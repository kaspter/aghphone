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

#include "transceiver.h"
#include "restypes.h"
#include <portaudio.h>
#include <alsa/asoundlib.h>
#include <ccrtp/rtp.h>
#include <math.h>
#include <cstdio>
#include <sys/time.h>

using namespace std;
using namespace ost;

namespace agh {

static volatile int c_in=0;
static volatile int c_out=0;
static volatile int underflowCount=0;
static volatile long readyOnInput=0;
static volatile long readyOnOutput=0;

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
	++c_out;
	}
	
	//if(!data->inputReady) {
	sampleType *iptr = (sampleType*)data->inputBuffer;
	sampleType *iptr2 = (sampleType*)inputBuffer;
	for( unsigned long i=0;i<framesPerBuffer;i++ ) {
		*iptr++ =  *iptr2++;
	}
	//data->inputReady = true;
	++c_in;
	
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
		
	++c_in;
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
		underflowCount++;
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
	
	++c_out;
	return paContinue;
}

/*
 *  PortAudio have to be initialized before running this c'tor
 */
DevicePa::DevicePa(int index)
{
	const   PaDeviceInfo *deviceInfo;
    PaStreamParameters inputParameters, outputParameters;
    PaError err;
    
    static double standardSampleRates[] = {
        8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
        44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1 /* negative terminated  list */
    };    
    
    deviceInfo = Pa_GetDeviceInfo( index );

	name = deviceInfo->name;
	id = index;
	hostAPI = Pa_GetHostApiInfo( deviceInfo->hostApi )->name;
	channelCountInput = deviceInfo->maxInputChannels;
	channelCountOutput = deviceInfo->maxOutputChannels;
	defLowInputLat = deviceInfo->defaultLowInputLatency;
	defLowOutputLat = deviceInfo->defaultLowOutputLatency;
	defHighInputLat = deviceInfo->defaultHighInputLatency;
	defHighOutputLat = deviceInfo->defaultHighOutputLatency;
	defSampleRate = deviceInfo->defaultSampleRate;	

	/* poll for standard sample rates */
	inputParameters.device = index;
    inputParameters.channelCount = deviceInfo->maxInputChannels;
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
    inputParameters.hostApiSpecificStreamInfo = NULL;
    
    outputParameters.device = index;
    outputParameters.channelCount = deviceInfo->maxOutputChannels;
    outputParameters.sampleFormat = paInt16;
    outputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
    outputParameters.hostApiSpecificStreamInfo = NULL;

    if( inputParameters.channelCount > 0 ) {
    	for(int i=0; standardSampleRates[i] > 0; i++ ) {
        	err = Pa_IsFormatSupported( &inputParameters, NULL, standardSampleRates[i] );
        	if( err == paFormatIsSupported )
        		sampleRatesHalfDupInput.push_back(standardSampleRates[i]);
    	}
    }

    if( outputParameters.channelCount > 0 ) {
    	for(int i=0; standardSampleRates[i] > 0; i++ ) {
        	err = Pa_IsFormatSupported( NULL, &outputParameters, standardSampleRates[i] );
        	if( err == paFormatIsSupported )
        		sampleRatesHalfDupOutput.push_back(standardSampleRates[i]);
    	}
    }

    if( inputParameters.channelCount > 0 && outputParameters.channelCount > 0 ) {
		for(int i=0; standardSampleRates[i] > 0; i++ ) {
        	err = Pa_IsFormatSupported( &inputParameters, &outputParameters, standardSampleRates[i] );
        	if( err == paFormatIsSupported )
        		sampleRatesFullDup.push_back(standardSampleRates[i]);
    	}
    }
}

DeviceFactoryPa::DeviceFactoryPa()
{
	deviceCount = Pa_GetDeviceCount();
	
	for(int i=0; i<deviceCount; i++)
		devs.push_back( new DevicePa(i) );
	
	cout << "Found " << deviceCount << " supported audio devices." << endl;
}

IDevice& DeviceFactoryPa::getDefaultInputDevice() const
{
	return getDevice(Pa_GetDefaultInputDevice());
}

IDevice& DeviceFactoryPa::getDefaultOutputDevice() const
{
	return getDevice(Pa_GetDefaultOutputDevice());
}

class CallbackMonitor : public Thread {
public:
	CallbackMonitor() {}
	~CallbackMonitor() {}
	
	void run()
	{
		while(1) {
			Thread::sleep(1000);
			printf("c_in: %d , c_out: %d, underflows: %d, readyOnInput: %ld, readyOnOutput: %ld\n", 
				c_in, c_out, underflowCount, readyOnInput, readyOnOutput);
			c_in = 0;
			c_out = 0;
		}
	}
	
};

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
	
	CallbackMonitor *cm = new CallbackMonitor();
	
	cm->start();
	
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




/* TransceiverAlsa implementation */

TransceiverAlsa::TransceiverAlsa()
{
	devMgr = new DeviceFactoryAlsa();
	
	setInputDevice(devMgr->getDefaultInputDevice());
	setOutputDevice(devMgr->getDefaultOutputDevice());
	
	playback_handle = NULL;
	adr = false;
	readyFrames = 0;
	delay = 0.0;
	frame_size = 160;
	shortBuffer = new short[65536];
	samples = new short[1024];
	audioBuffer = new float[4096];
	sample_rate = 8000;
	
	inputBufferSize = 4096;
	inputBufferCursor = 0;
	inputBufferCursor2 = 0;
	inputBufferReady = 0;
	outputBufferSize = 4096;
	outputBufferCursor = 0;
	outputBufferCursor2 = 0;
	outputBufferReady = 0;
	
	initTime();
	resetTimerMs();
}

TransceiverAlsa::~TransceiverAlsa()
{
	delete shortBuffer;
	delete samples;
	delete audioBuffer;
	
	if( tCore )
		delete tCore;
	
	if( rCore )
		delete rCore;
	
	delete socket;
	cout << "RTP session closed" << endl;
}

vector<IDevice*> TransceiverAlsa::getAvailableInputDevices() const
{
	vector<IDevice*> v;
	
	return v;
}

vector<IDevice*> TransceiverAlsa::getAvailableOutputDevices() const
{
	vector<IDevice*> v;
	
	return v;
}

int TransceiverAlsa::setInputDevice(const IDevice& dev)
{
	inputDevice = &dev;
	
	return 0;
}

int TransceiverAlsa::setInputDevice(const int id)
{
	//inputDevice = &devMgr->getDevice(id);
	
	return 0;
}

int TransceiverAlsa::setOutputDevice(const IDevice& dev)
{
	outputDevice = &dev;
	
	return 0;
}

int TransceiverAlsa::setOutputDevice(const int id)
{
	//outputDevice = &devMgr->getDevice(id);
	
	return 0;
}

int TransceiverAlsa::setCodec(int codec)
{
	/*
	 *  TODO: Implement codec factory to get a codec object by id 
	 */ 
	 
	return 0;
}

int TransceiverAlsa::setLocalEndpoint(const IPV4Address& addr, int port)
{
	localAddress = addr;
	localPort = port;
	
	return 0;
}

int TransceiverAlsa::setRemoteEndpoint(const IPV4Address& addr, int port)
{
	remoteAddress = addr;
	remotePort = port;
	
	return 0;
}

int TransceiverAlsa::start()
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
	tCore = new TransmitterAlsaCore(this);
	
	cout << "Creating Receiver core" << endl;
	rCore = new ReceiverAlsaCore(this);

	//socket = new SymmetricRTPSession( IPV4Host(localAddress.getAddress()), localPort );
	socket = new AghRtpSession( IPV4Host(localAddress.getAddress()), localPort );

	//socket->setSchedulingTimeout(10000);
	socket->setExpireTimeout(51);
	
	
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
	
	CallbackMonitor *cm = new CallbackMonitor();
	
	cm->start();
	
	return TransceiverStartResult::SUCCESS;
}

int TransceiverAlsa::stop()
{
	if( tCore )
		delete tCore;
	
	return 0;
}

TransmitterAlsaCore::TransmitterAlsaCore(TransceiverAlsa* tpa)
{
	t = tpa;
}

TransmitterAlsaCore::~TransmitterAlsaCore()
{
	terminate();
	snd_pcm_drop(t->capture_handle);
	snd_pcm_close(t->capture_handle);
	t->capture_handle = NULL;
}

void TransmitterAlsaCore::run()
{	
	setCancel(cancelImmediate);

	int err = snd_pcm_start(t->capture_handle);
	if(err < 0) cout << "Alsa error : cannot start capture stream : " << snd_strerror(err) << endl;

  	if( t->socket->RTPDataQueue::isActive() )
		cout << "active." << endl;
	else
	    cerr << "not active." << endl;

	TimerPort::setTimer(20);
	
	int packetCounter = 1;
	int samples=t->framesPerBuffer*t->sample_rate/8000; // <-----!!----->
	//int size = samples*2;
	
	unsigned char buf[2048];
	
	unsigned char *outbuf;
	
	short mybuf[2*1024*1024];
	long msbuf[2][50*1024];
	unsigned long mybuf_index = 0;
	long sendCounter=0;
	
	int nperiods = 20;
	int periodsize = t->framesPerBuffer*sizeof(sampleType);
	outbuf = new unsigned char[nperiods*periodsize];
	int outbufcursor=0;
	//uint32 timestamp = t->socket>getCurrentTimestamp() + 160*packetCounter;
	uint32 timestamp = t->socket->getCurrentTimestamp() + sizeof(sampleType)*t->framesPerBuffer;
	
	int phase=0;
	
	while(1) {
		if(t->alsa_can_read(t->capture_handle, samples)) {
			
			int err = t->alsa_read(t->capture_handle, buf, samples);
			
			if(err <= 0) {
				cout << "Failed to read samples from capture device " << snd_strerror(err) << endl;
			} else {
				//printf("read %d frames from input at ", err);
				//t->printTime();
				
				//  ---- !! ---
			
				for(int i=0;i<err;i++) {
					((sampleType*)buf)[i] = (sampleType)(sin((((double)phase/20.0)*3.1415926535897931))*16000.0);
					phase++;
					if(phase > 40)
						phase = 0;
				}
				//err	= 160;
			
				// ----- !! ----
				
				sampleType *optr = t->inputBuffer + t->inputBufferCursor;
				sampleType *ptr = (sampleType*)buf;
			   	
			   	long toEnd = t->inputBufferSize - t->inputBufferCursor;
			   	
			   	if(toEnd >= err ) {
			   		for(long i=0;i<err;i++) *optr++ = *ptr++;
			   	} else {
			   		for(long i=0;i<toEnd;i++) *optr++ = *ptr++;
			   		optr = t->inputBuffer;
			   		for(long i=0;i<err-toEnd;i++) *optr++ = *ptr++;
			   	}
			   	
			   	t->inputBufferCursor += err;
			   	if(t->inputBufferCursor >= t->inputBufferSize)
			   		t->inputBufferCursor -= t->inputBufferSize;	
			   	
			   	t->inputBufferReady += err;
			   	
			   	
			   	
				if( t->inputBufferReady >= 160 ) {
					sampleType *ptr1 = t->inputBuffer + t->inputBufferCursor2;
					sampleType *ptr2 = (sampleType*)(outbuf + outbufcursor*periodsize);
					
					long toEnd2 = t->inputBufferSize - t->inputBufferCursor2;
					
					if(toEnd2 >= 160) {
						for(int i=0;i<160;i++) *ptr2++ = *ptr1++;
					} else {
						for(int i=0;i<toEnd2;i++) *ptr2++ = *ptr1++;
						ptr1 = t->inputBuffer;
						for(int i=0;i<160-toEnd2;i++) *ptr2++ = *ptr1++;
					}
					
					t->inputBufferCursor2 += 160;
					if(t->inputBufferCursor2 >= t->inputBufferSize)
						t->inputBufferCursor2 -= t->inputBufferSize;
						
					t->inputBufferReady -= 160;
					
/*					// ------ !! ----
					sampleType *ptr3=(sampleType*)(outbuf+outbufcursor*periodsize);
					for(int i=0;i<160;i++) {
						if( (ptr3[i] != (sampleType)0) && (ptr3[i] != (sampleType)1000) ) {
							cout << "ZORRO ERRORRO : outbufcursor:" << outbufcursor <<
							", inputBufferCursor:" << t->inputBufferCursor << ", inputBufferCursor2:" <<
							t->inputBufferCursor2 << ", toEnd:" << toEnd << ", toEnd2:" << toEnd2 << 
							", ready:" << t->inputBufferReady << ", packetCounter:" << packetCounter <<
							",i:" << i << ",ptr3[i]:" << ptr3[i] << endl;
							 break;
						}
					}
					// ------ !! ----
*/					

//	  				t->socket->sendImmediate(160*sizeof(sampleType)*packetCounter,(const unsigned char *)(outbuf + outbufcursor*periodsize), 160*sizeof(sampleType));
					//t->socket->putData(160*16*packetCounter,(const unsigned char *)(outbuf + outbufcursor*periodsize), 160*sizeof(sampleType));
					
					
					
					
					
									
				msbuf[0][sendCounter] = mybuf_index;
				msbuf[1][sendCounter] = t->getTimeMs();
	
				if (mybuf_index >= 50*1024) {
					cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
					FILE *file2 = fopen("danes.txt", "w");
					FILE *file3 = fopen("timingis.txt", "w");
					cout << "dupa1" <<  endl;
					cout << "dupa1" <<  endl;
					
					long i=0;
					while(i < 50*1024) {
						fprintf(file2, "%ld\t%d\n", i, mybuf[i]);
						i++;
					}
					
					for(i=0;i<sendCounter;i++)
						fprintf(file3, "%ld\t%ld\n", msbuf[0][i], msbuf[1][i]);
					
					mybuf_index = 0;
					cout << "dupa1" <<  endl;
					fclose(file2);
					fclose(file3);
					cout << "dupa1" <<  endl;
				}
				memcpy(mybuf+mybuf_index, (const unsigned char *)(outbuf + outbufcursor*periodsize), err*sizeof(sampleType));
				mybuf_index += 160;

				sendCounter++;
					
					
					
					
					
					
					t->socket->setExpireTimeout(320 * 1000);
					t->socket->putData(timestamp, (const unsigned char *)(outbuf + outbufcursor*periodsize), 160*sizeof(sampleType));

	  				packetCounter++;
					timestamp += 160;
	  				c_in = outbufcursor;
	  				
	  				outbufcursor++;
	  				if(outbufcursor >= nperiods)
	  					outbufcursor = 0;
	  				
			  		TimerPort::incTimer(20);
	  				Thread::sleep(TimerPort::getTimer());
				}
				
				readyOnInput = t->inputBufferReady;
			}
		}
    }
}

ReceiverAlsaCore::ReceiverAlsaCore(TransceiverAlsa* tpa)
{
	t = tpa;
}

ReceiverAlsaCore::~ReceiverAlsaCore()
{
	terminate();
	snd_pcm_drop(t->playback_handle);
	snd_pcm_close(t->playback_handle);
	t->playback_handle = NULL;
}

void ReceiverAlsaCore::run()
{	
	TimerPort::setTimer(20);
	
	unsigned char buf[2048];
	short mybuf[2*1024*1024];
	long msbuf[2][50*1024];
	unsigned long mybuf_index = 0;
	long recvCounter=0;
	
	while(1) {	
  		long size;
	  	const AppDataUnit* adu;
	  	//do {
	  		adu = t->socket->getData(t->socket->getFirstTimestamp());
	  		//if( NULL == adu )
	  		//	Thread::sleep(5);
	  	if ( (NULL != adu) && ( (size = adu->getSize()/2) > 0 ) ) {
	  		
//	    cout << "recvd packet of size " << size << " ready:" << t->outputBufferReady << endl;
		   	sampleType *ptr = (sampleType*)adu->getData();
			sampleType *optr = t->outputBuffer + t->outputBufferCursor;
			
			msbuf[0][recvCounter] = mybuf_index;
			msbuf[1][recvCounter] = t->getTimeMs();

			if (mybuf_index >= 50*1024) {
				cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
				FILE *file = fopen("dupencja.dat", "w");
				FILE *file2 = fopen("dane.txt", "w");
				FILE *file3 = fopen("timingi.txt", "w");
				cout << "dupa1" <<  endl;
				cout << "dupa1" <<  endl;
				fwrite(mybuf, sizeof(sampleType),  50*1024, file);
				
				long i=0;
				while(i < 50*1024) {
					fprintf(file2, "%ld\t%d\n", i, mybuf[i]);
					i++;
				}
				
				for(i=0;i<recvCounter;i++)
					fprintf(file3, "%ld\t%ld\n", msbuf[0][i], msbuf[1][i]);
				
				mybuf_index = 0;
				cout << "dupa1" <<  endl;
				fclose(file);
				fclose(file2);
				fclose(file3);
				cout << "dupa1" <<  endl;
			}
			memcpy(mybuf+mybuf_index, ptr, size*sizeof(sampleType));
			mybuf_index += size;
			c_in = mybuf_index;
			
			long toEnd = t->outputBufferSize - t->outputBufferCursor;
			if(toEnd >= size ) {
				for(long i=0;i<size;i++) *optr++ = *ptr++;
			} else {
				for(long i=0;i<toEnd;i++) *optr++ = *ptr++;
				optr = t->outputBuffer;
				for(long i=0;i<size-toEnd;i++) *optr++ = *ptr++;
			}
				   	
			t->outputBufferCursor += size;
			if(t->outputBufferCursor >= t->outputBufferSize)
				t->outputBufferCursor -= t->outputBufferSize;	
				   	
			t->outputBufferReady += size;
			
			
			recvCounter++;
	  	}
			   					
		while( t->outputBufferReady >= t->framesPerBuffer ) {
			sampleType *ptr1 = t->outputBuffer + t->outputBufferCursor2;
			sampleType *ptr2 = (sampleType*)buf;
					
			long toEnd2 = t->outputBufferSize - t->outputBufferCursor2;
					
			if(toEnd2 >= t->framesPerBuffer) {
				for(int i=0;i<t->framesPerBuffer;i++) *ptr2++ = *ptr1++;
			} else {
				for(int i=0;i<toEnd2;i++) *ptr2++ = *ptr1++;
				ptr1 = t->outputBuffer;
				for(int i=0;i<t->framesPerBuffer-toEnd2;i++) *ptr2++ = *ptr1++;
			}
			
//			int err = t->alsa_write(t->playback_handle,  buf, t->framesPerBuffer);
			int err = 160;
			if(err > 0) {
				
//				printf("written %d frames to output at ", err);
//				t->printTime();
				
				t->outputBufferReady -= err;
				t->outputBufferCursor2 += err;
				if(t->outputBufferCursor2  >= t->outputBufferSize)
					t->outputBufferCursor2 -= t->outputBufferSize;
	  			
	  			c_out++;
	  				 	
//	  		 	TimerPort::incTimer(20);
//	  			Thread::sleep(TimerPort::getTimer());
			} else {
				//cout << "Couldn't write to the playback device. Tried to write " <<
				//t->framesPerBuffer*sizeof(sampleType) << " bytes of data." << endl;
				Thread::sleep(5);
				break;
			}
		}
		readyOnOutput = t->outputBufferReady;
    }
}

void TransceiverAlsa::openStream()
{
	int err;
	snd_output_t *log;
	
	snd_output_stdio_attach(&log, stderr, 0);
	
	err = snd_pcm_open(&capture_handle, inputDevice->getName().c_str(), SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK);
	if(err < 0) cout << "Alsa error : cannot open capture device (" << inputDevice->getName() << ") : " << snd_strerror(err) << endl;
	
	alsa_set_params(capture_handle, 0);
	
	cout << "[Capture device]:" << endl;
	snd_pcm_dump(capture_handle, log);
	
	err = snd_pcm_open(&playback_handle, outputDevice->getName().c_str(), SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
	if(err < 0) cout << "Alsa error : cannot open playback device (" << outputDevice->getName() << "): " << snd_strerror(err) << endl;
	
	alsa_set_params(playback_handle, 1);
	
	cout << "[Playback device]:" << endl;
	snd_pcm_dump(playback_handle, log);
	
}

snd_pcm_t* TransceiverAlsa::alsa_set_params(snd_pcm_t *pcm_handle, int rw)
{
	snd_pcm_hw_params_t *hwparams = NULL;
	snd_pcm_sw_params_t *swparams = NULL;
	int dir;
	uint exact_uvalue;
	unsigned long exact_ulvalue;
	int channels = 1;
	int err;
	int rate = 8000;
	/*
	 * TODO : [!!!!!] check if periodsize is in samples or in bytes if in samples it should be 160
	 */
	int periodsize = 160;
	int periods = 8;
	snd_pcm_format_t format = SND_PCM_FORMAT_S16;
	
	snd_pcm_hw_params_alloca(&hwparams);
	
	err = snd_pcm_hw_params_any(pcm_handle, hwparams);
	if(err < 0) cout << "Alsa error: cannot initialize hw params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_access(pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err < 0) cout << "Alsa error: cannot set access type : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_format(pcm_handle, hwparams, format);
	if(err < 0) cout << "Alsa error: cannot set sample format : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_channels(pcm_handle, hwparams, channels);
	if(err < 0) cout << "Alsa error: cannot set channel count : " << snd_strerror(err) << endl;
	
	exact_uvalue = rate;
	dir = 0;
	err = snd_pcm_hw_params_set_rate_near(pcm_handle, hwparams, &exact_uvalue, &dir);
	if(err < 0) cout << "Alsa error: cannot set sample rate : " << snd_strerror(err) << endl;
	if(dir != 0) cout << "Alsa error: " << rate << 
		" Hz sample rate is not supported by your hardware. Using " << exact_uvalue << " Hz instead." << endl;
	
	periodsize = periodsize*(rate/8000);
	exact_ulvalue=periodsize;
	dir=0;
	err = snd_pcm_hw_params_set_period_size_near(pcm_handle, hwparams, &exact_ulvalue, &dir);
	if(err < 0) cout << "Alsa error: cannot set period size : " << snd_strerror(err) << endl;
	if(dir != 0) cout << "Alsa error: " << periodsize << 
		" period size is not supported by your hardware. Using " << exact_ulvalue << " instead." << endl;
	periodsize = exact_ulvalue;
	this->framesPerBuffer = periodsize;
		  
	exact_uvalue=periods;
	dir = 0; 
	err = snd_pcm_hw_params_set_periods_near(pcm_handle, hwparams, &exact_uvalue, &dir);
	if(err < 0) cout << "Alsa error: cannot set periods : " << snd_strerror(err) << endl;
	if(dir != 0) cout << "Alsa error: " << periods << 
		" periods is not supported by your hardware. Using " << exact_uvalue << " instead." << endl;
	
	err = snd_pcm_hw_params(pcm_handle, hwparams);
	if(err < 0) cout << "Alsa error: cannot hw parameters : " << snd_strerror(err) << endl;
	
	if(rw) {
		snd_pcm_sw_params_alloca(&swparams);
		snd_pcm_sw_params_current(pcm_handle, swparams);
		err = snd_pcm_sw_params_set_start_threshold(pcm_handle, swparams, periodsize*2);
		if(err < 0) cout << "Alsa error: cannot start threshold : " << snd_strerror(err) << endl;
		
		err = snd_pcm_sw_params_set_stop_threshold(pcm_handle, swparams, periodsize*periods);
		if(err < 0) cout << "Alsa error: cannot stop threshold : " << snd_strerror(err) << endl;
		
		err = snd_pcm_sw_params(pcm_handle, swparams);
		if(err < 0) cout << "Alsa error: cannot start sw params : " << snd_strerror(err) << endl;
	
	}
	
	return 0;
}

bool TransceiverAlsa::alsa_can_read(snd_pcm_t *dev, int frames)
{
	snd_pcm_sframes_t avail;
	int err;
	
	avail = snd_pcm_avail_update(dev);
	if(avail < 0) {
		snd_pcm_drain(dev);
		err = snd_pcm_recover(dev, avail, 0);
		if(err) cout << "Alsa error: snd_pcm_recover failed on capture device : " << snd_strerror(err) << endl;
		err = snd_pcm_start(dev);
		if(err) cout << "Alsa error: snd_pcm_start failed after recover on capture device : " << snd_strerror(err) << endl;
	}
	
	return avail >= frames;
}

int TransceiverAlsa::alsa_read(snd_pcm_t *handle, unsigned char* buf, int nsamples)
{
	int err;
	err = snd_pcm_readi(handle, buf, nsamples);
	if(err < 0) {
		if(err == -EPIPE) {
			snd_pcm_prepare(handle);
			err = snd_pcm_readi(handle, buf, nsamples);
			if(err < 0) cout << "Alsa error : snd_pcm_readi failed : " << snd_strerror(err) << endl;
		} else if(err == 0) {
			cout << "snd_pcm_readi return 0" << endl;
		}
	}
	
	return err;
}

int TransceiverAlsa::alsa_write(snd_pcm_t *handle, unsigned char* buf, int nsamples)
{
	int err;
	if ((err = snd_pcm_writei(handle, buf, nsamples)) < 0) {
		if(err == -EPIPE) {
			snd_pcm_prepare(handle);
			alsa_fill_w(handle);
			err = snd_pcm_writei(handle, buf, nsamples);
			if(err < 0) cout << "Alsa error : failed writing " << nsamples << " samples on output device : " << snd_strerror(err) << endl;
		} else if(err != -EWOULDBLOCK) {
			cout << "Alsa error : snd_pcm_writei failed : " << snd_strerror(err) << endl;
		}
	} else if(err!=nsamples) {
		cout << "Alsa warning : only " << err << " samples written instead of " << nsamples << endl;
	}
	return err;
}

void TransceiverAlsa::alsa_fill_w(snd_pcm_t *pcm_handle)
{
	snd_pcm_hw_params_t *hwparams=NULL;
	int channels;
	snd_pcm_uframes_t buffer_size;
	int buffer_size_bytes;
	void *buffer;
	
	snd_pcm_hw_params_alloca(&hwparams);
	snd_pcm_hw_params_current(pcm_handle, hwparams);
	
	snd_pcm_hw_params_get_channels(hwparams, (unsigned int*)&channels);
	snd_pcm_hw_params_get_buffer_size(hwparams, &buffer_size);
	buffer_size /= 2;
	buffer_size_bytes = buffer_size*channels*2;
	/*
	 * TODO: here buffer is allocated but the memory is not freed later
	 * 		check if we can free it right after snd_pcm_writei
	 */
	buffer = alloca(buffer_size_bytes);
	memset(buffer, 0, buffer_size_bytes);
	snd_pcm_writei(pcm_handle, buffer, buffer_size);
}

void TransceiverAlsa::initTime() {
	gettimeofday(&czas_start, NULL);
}

void TransceiverAlsa::printTime() {
	struct timeval czas_teraz;
	
	gettimeofday(&czas_teraz, NULL);
	
	printf("%3ld.%3ld [s]\n", czas_teraz.tv_sec - czas_start.tv_sec, czas_teraz.tv_usec/1000); 
}

void TransceiverAlsa::resetTimerMs() {
	gettimeofday(&startMs, NULL);
}

long TransceiverAlsa::getTimeMs() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec - startMs.tv_sec)*1000 + tv.tv_usec/1000;
}


AghRtpSession::AghRtpSession(const InetHostAddress &host) :
	SymmetricRTPSession(host) 
{
}

AghRtpSession::AghRtpSession(const InetHostAddress &host, unsigned short port) : 
	SymmetricRTPSession(host, port) 
{
}

uint32 AghRtpSession::getLastTimestamp(const SyncSource *src) const {
	if ( src && !isMine(*src) ) return 0L;
	
	recvLock.readLock();

	uint32 ts = 0;	
	if (src != NULL) {
		SyncSourceLink* srcm = getLink(*src);
		IncomingRTPPktLink* l = srcm->getFirst();
		
		while (l) {
			ts = l->getTimestamp();
			l = l->getSrcNext();
		}
	} else {
		IncomingRTPPktLink* l = recvFirst;
		
		while (l) {
			ts = l->getTimestamp();
			l = l->getNext();
		}
	}
	
	recvLock.unlock();
	return ts;
}



} /* namespace agh */
