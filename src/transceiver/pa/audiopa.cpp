/*
 * Copyright (C) 2008  Mateusz Kramarczyk <kramarczyk (at) gmail (dot) com>
 * Copyright (C) 2008  Tomasz Kijas <kijasek (at) gmail (dot) com>
 * Copyright (C) 2008  Tomir Kryza <tkryza (at) gmail (dot) com>
 * Copyright (C) 2008  Maciej Kluczny <kluczny (at) fr (dot) pl>
 * Copyright (C) 2008  AGH University of Science and Technology <www.agh.edu.pl>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "transceiverpa.h"
#include "restypes.h"
#include <ccrtp/rtp.h>
#include <portaudio.h>

using namespace std;
using namespace ost;

namespace agh {

static int callback( const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
 	                  const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData )
{
	CallbackData *data = (CallbackData*)userData;

	(void) timeInfo;
	
	if(data->outputReady) {
	sampleType *optr = (sampleType*)data->outputBuffer;
	sampleType *optr2 = (sampleType*)outputBuffer;
	for( unsigned long i=0;i<framesPerBuffer;i++ ) {
		*optr2++ = *optr++;
	}
	data->outputReady = false;
//	++c_out;
	}
	
	//if(!data->inputReady) {
	sampleType *iptr = (sampleType*)data->inputBuffer;
	sampleType *iptr2 = (sampleType*)inputBuffer;
	for( unsigned long i=0;i<framesPerBuffer;i++ ) {
		*iptr++ =  *iptr2++;
	}
	//data->inputReady = true;
//	++c_in;
	
	return paContinue;
}

static int callbackInput(  const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
 	                  const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData )
{
	CallbackData *data = (CallbackData*)userData;

	(void) timeInfo;

	sampleType *ptr = (sampleType*)data->inputBuffer;
	sampleType *iptr = (sampleType*)inputBuffer;
	for( unsigned long i=0;i<framesPerBuffer;i++ )
		*ptr++ =  *iptr++;
		
//	++c_in;
	return paContinue;
}

static int callbackOutput(  const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
 	                  const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData )
{
	CallbackData *data = (CallbackData*)userData;

	(void) timeInfo;

	sampleType *optr = (sampleType*)outputBuffer;
	if(data->ringBufferReadIndex == data->ringBufferWriteIndex) {
		for(unsigned int i=0;i<framesPerBuffer;i++) {
			*optr++ = 0;
		}
//		underflowCount++;
	} else {
		sampleType *ptr = (sampleType*)data->ringBuffer + data->ringBufferReadIndex;
		unsigned int toEnd = data->ringBufferEnd - optr;
		
		if(toEnd >= framesPerBuffer ) {
			for(unsigned int i=0;i<framesPerBuffer;i++)
		   		*optr++ = *ptr++;
		} else {
		   	for(unsigned int i=0;i<toEnd;i++)
		   		*optr++ = *ptr++;
		   	ptr = data->ringBuffer;
		   	for(unsigned int i=0;i<framesPerBuffer-toEnd;i++)
		   		*optr++ = *ptr++;
		}
	   	
		data->ringBufferReadIndex += framesPerBuffer;
		if(data->ringBufferReadIndex >= RING_BUFFER_SIZE)
			data->ringBufferReadIndex -= RING_BUFFER_SIZE;
	}
	
//	++c_out;
	return paContinue;
}

TransceiverPa::TransceiverPa()
{
	PaError err = Pa_Initialize();

	if( err != paNoError ) {
		/*
		 * TODO: Implement logging of portaudio initialization failure
		 */
		 cout << Pa_GetErrorText(err) << endl;
	} else {
		devMgr = new DeviceFactoryPa();
		
		inputDevice = &devMgr->getDefaultInputDevice();
		outputDevice = &devMgr->getDefaultOutputDevice();
		
		localPort = -1;
		remotePort = -1;
		framesPerBuffer = 160;
		
		tCore = NULL;
		cout << "Transceiver created successfuly" << endl;
	}
}

TransceiverPa::~TransceiverPa()
{
	Pa_AbortStream(inputStream);
	Pa_AbortStream(outputStream);
	Pa_CloseStream(inputStream);
	Pa_CloseStream(outputStream);
	cout << "audio stream closed" << endl;
	
	if( devMgr )
		delete devMgr;
	
	if( tCore )
		delete tCore;
	
	if( rCore )
		delete rCore;
	
	delete socket;
	cout << "RTP session closed" << endl;
		
	//Pa_CloseStream(stream);
	
	Pa_Terminate();
	cout << "portaudio terminated" << endl;
}

vector<IDevice*> TransceiverPa::getAvailableInputDevices() const
{
	vector<IDevice*> v;
	
	return v;
}

vector<IDevice*> TransceiverPa::getAvailableOutputDevices() const
{
	vector<IDevice*> v;
	
	return v;
}

int TransceiverPa::setInputDevice(const IDevice& dev)
{
	inputDevice = &dev;
	
	return 0;
}

int TransceiverPa::setInputDevice(const int id)
{
	inputDevice = &devMgr->getDevice(id);
	
	return 0;
}

int TransceiverPa::setOutputDevice(const IDevice& dev)
{
	outputDevice = &dev;
	
	return 0;
}

int TransceiverPa::setOutputDevice(const int id)
{
	outputDevice = &devMgr->getDevice(id);
	
	return 0;
}

int TransceiverPa::setCodec(int codec)
{
	/*
	 *  TODO: Implement codec factory to get a codec object by id 
	 */ 
	 
	return 0;
}

int TransceiverPa::setLocalEndpoint(const IPV4Address& addr, int port)
{
	localAddress = addr;
	localPort = port;
	
	return 0;
}

int TransceiverPa::setRemoteEndpoint(const IPV4Address& addr, int port)
{
	remoteAddress = addr;
	remotePort = port;
	
	return 0;
}

int TransceiverPa::start()
{
	if( (localPort == -1 ) ) {
		cout << "Endpoint error: " << localAddress << ":" << localPort << endl;
		return TransceiverStartResult::LOCAL_ENDPOINT_ERROR;
	}
	
	if( ( remotePort == -1 ) || ( !remoteAddress) ) {
		printf("error2\n");
		return TransceiverStartResult::REMOTE_ENDPOINT_ERROR;
	}
	
	cout << "Opening streams" << endl;
	openStream();
	
	cout << "Creating Transmitter core" << endl;
	tCore = new TransmitterCore(this);
	
	cout << "Creating Receiver core" << endl;
	rCore = new ReceiverCore(this);

	socket = new AghRtpSession( IPV4Host(localAddress.getAddress()), localPort );

	//socket->setSchedulingTimeout(10000);
	socket->setExpireTimeout(50);
	
	
	if( !socket->addDestination( IPV4Host(remoteAddress.getAddress()), remotePort ) ) {
		/*
		 * TODO: Implement ccrtp connection failure
		 */
		cout << "CCRTP destination connection failure: " << IPV4Host(remoteAddress.getAddress()) << ":" << remotePort << endl;
		return -1;
	}
	
	socket->setPayloadFormat( StaticPayloadFormat( sptPCMU ) );

	socket->startRunning();
	
	cData.socket = socket;
	cData.packetCounter = 0;
	
	tCore->start();
	cout << "Transmitter core started" << endl;
	
	rCore->start();
	cout << "Receiver core started" << endl;
	
//	CallbackMonitor *cm = new CallbackMonitor();
	
//	cm->start();
	
	return TransceiverStartResult::SUCCESS;
}

int TransceiverPa::stop()
{
	if( tCore )
		delete tCore;
	
	return 0;
}

TransmitterCore::TransmitterCore(TransceiverPa* tpa)
{
	t = tpa;
}

TransmitterCore::~TransmitterCore()
{
	terminate();
}

void TransmitterCore::run()
{	
	setCancel(cancelImmediate);


  	if( t->socket->RTPDataQueue::isActive() )
		cout << "active." << endl;
	else
	    cerr << "not active." << endl;

	
	TimerPort::setTimer(20);
	
	int packetCounter = 0;
	
	while(1) {
	  		t->socket->sendImmediate(t->framesPerBuffer*sizeof(sampleType)*packetCounter,(const unsigned char *)t->cData.inputBuffer, t->framesPerBuffer*sizeof(sampleType));
	  		packetCounter++;
	  		
	  		TimerPort::incTimer(20);
	  		Thread::sleep(TimerPort::getTimer());
    }
}

ReceiverCore::ReceiverCore(TransceiverPa* tpa)
{
	t = tpa;
}

ReceiverCore::~ReceiverCore()
{
	terminate();
}

void ReceiverCore::run()
{	
	setCancel(cancelImmediate);
		
	TimerPort::setTimer(20);
	
//	for(int i=0; i<160; i++)
//		t->cData.outputBuffer[i] = 0;

	//sampleType tmpBuffer[2097152]; // 4MB buffer
	//int tmpWrite=0;
	//int tmpToWrite=3000;
	//sampleType *tmpPtr=tmpBuffer;
	//int tmpCtr=0;
	while(1) {
		
  		long size;
	  	const AppDataUnit* adu;
	  	do {
	  		adu = t->socket->getData(t->socket->getFirstTimestamp());
	  		if( NULL == adu )
	  			Thread::sleep(5);
	  	} while ( (NULL == adu) || ( (size = adu->getSize()) <= 0 ) );
	    
	   	sampleType *ptr = (sampleType*)adu->getData();
	   	
	   	/*
	   	if(tmpWrite < tmpToWrite) {
	   		memcpy(tmpPtr, ptr, t->framesPerBuffer*sizeof(sampleType));
	   		tmpPtr+=t->framesPerBuffer*sizeof(sampleType);
	   		tmpWrite++;
	   		if(! (tmpWrite % 50) ) {
	   			printf("buffering... %d/%d\n", tmpWrite, tmpToWrite); fflush(stdout);
	   		}
	   	} else {
	   		char fname[10];
	   		sprintf(fname, "dump%d", tmpCtr++);
	   		printf("dumping to file %s ...\n", fname);  fflush(stdout);
	   		FILE *fout = fopen(fname, "wb");
	   		fwrite(tmpBuffer, sizeof(sampleType), tmpWrite*t->framesPerBuffer, fout);
	   		fclose(fout);
	   		tmpWrite=0;
	   	}
	   	*/
	   	
	   	sampleType *optr = t->cData.ringBuffer + t->cData.ringBufferWriteIndex;
	   	
	   	int toEnd = t->cData.ringBufferEnd - optr;
	   	if(toEnd >= 160 ) {
	   		for(int i=0;i<160;i++)
	   			*optr++ = *ptr++;
	   	} else {
	   		for(int i=0;i<toEnd;i++)
	   			*optr++ = *ptr++;
	   		optr = t->cData.ringBuffer;
	   		for(int i=0;i<160-toEnd;i++)
	   			*optr++ = *ptr++;
	   	}
	   	
	   	t->cData.ringBufferWriteIndex += 160;
	   	if(t->cData.ringBufferWriteIndex >= RING_BUFFER_SIZE)
	   		t->cData.ringBufferWriteIndex -= RING_BUFFER_SIZE;
    }
}

void TransceiverPa::openStream()
{
	cout << "Opening streams, sample size: " << sizeof(sampleType) << ", sample rate: " << 8000 << endl;
	
	PaStreamParameters inputParameters, outputParameters;
	PaError err;
	
	bzero(&inputParameters, sizeof(PaStreamParameters));
	bzero(&outputParameters, sizeof(PaStreamParameters));
	
	
	inputParameters.device = inputDevice->getID(); /* default input device */
  	inputParameters.channelCount = 1;                    /* stereo input */
	inputParameters.sampleFormat = SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;
    
    outputParameters.device = outputDevice->getID(); /* default input device */
  	outputParameters.channelCount = 1;                    /* stereo input */
	outputParameters.sampleFormat = SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	
	/* SINGLE STREAM */
	
	/*
	
	err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, 8000, 160,
						paClipOff, callback, &cData);
	
	if(err != paNoError) {
		cout << Pa_GetErrorText(err) << endl;
		return;
	}
	*/
	
	 // TWO STREAMS
	
	err = Pa_OpenStream(&inputStream, &inputParameters, NULL, 8000.0, framesPerBuffer,
						paClipOff, callbackInput, &cData);
	
	if(err != paNoError) {
		cout << "Input stream opening error: " << Pa_GetErrorText(err) << endl;
		return;
	}
	
	err = Pa_OpenStream(&outputStream, NULL, &outputParameters, 00.0, framesPerBuffer,
						paClipOff, callbackOutput, &cData);
	
	if(err != paNoError) {
		cout << "Output stream opening error: " << Pa_GetErrorText(err) << endl;
		return;
	}
	


	cData.inputBuffer = new sampleType[framesPerBuffer];
	cData.outputBuffer = new sampleType[framesPerBuffer];
	cData.outputReady = false;
	cData.inputReady = false;
	
	for( int i=0; i<RING_BUFFER_SIZE; i++ )
		cData.ringBuffer[i] = 0;
	
	cData.ringBufferWriteIndex = 0;
	cData.ringBufferReadIndex = 0;
	cData.ringBufferEnd = cData.ringBuffer+RING_BUFFER_SIZE;
	
	  // SINGLE STREAM  
	
	/*err = Pa_StartStream(stream);
	
	if(err != paNoError) {
		cout << Pa_GetErrorText(err) << endl;
		return;
	}*/
	

	// TWO STREAMS
	
	err = Pa_StartStream(inputStream);
	if(err != paNoError) {
		cout << Pa_GetErrorText(err) << endl;
		return;
	}
	err = Pa_StartStream(outputStream);
	if(err != paNoError) {
		cout << Pa_GetErrorText(err) << endl;
		return;
	}
	

	cout << "Stream(s) opened successfully" << endl;	
} 

}
