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

using namespace std;
using namespace ost;

namespace agh {

static volatile int c_in=0;
static volatile int c_out=0;
static volatile int underflowCount=0;

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
			printf("c_in: %d , c_out: %d, underflows: %d\n", c_in, c_out, underflowCount);
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

	socket = new RTPSession( IPV4Host(localAddress.getAddress()), localPort );

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

	sampleType tmpBuffer[2097152]; // 4MB buffer
	int tmpWrite=0;
	int tmpToWrite=3000;
	sampleType *tmpPtr=tmpBuffer;
	int tmpCtr=0;
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
	playback_handle = NULL;
	adr = false;
	readyFrames = 0;
	delay = 0.0;
	frame_size = 160;
	shortBuffer = new short[65536];
	samples = new short[1024];
	audioBuffer = new float[4096];
	sample_rate = 8000;
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

	socket = new RTPSession( IPV4Host(localAddress.getAddress()), localPort );

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

	snd_pcm_start(t->capture_handle);

  	if( t->socket->RTPDataQueue::isActive() )
		cout << "active." << endl;
	else
	    cerr << "not active." << endl;

	
	TimerPort::setTimer(20);
	
	int packetCounter = 0;
	
	while(1) {
		int err = snd_pcm_readi(t->capture_handle, t->samples, 1024);
		if(err < 0) {
//			if(packetCounter % 50)
//				cout << "Alsa recording error: " << snd_strerror(err) << endl;
			snd_pcm_state_t pcm_state = snd_pcm_state(t->capture_handle);
			if(pcm_state == SND_PCM_STATE_XRUN) {
				snd_pcm_prepare(t->capture_handle);
				snd_pcm_start(t->capture_handle);
			}
		} else if (err > 0) {
			for(int i=0;i<err;i++)
				t->audioBuffer[i] = (float) t->samples[i];
				 
	  		t->socket->sendImmediate(err*sizeof(sampleType)*packetCounter,(const unsigned char *)t->samples, err*sizeof(sampleType));
	  		packetCounter++;
	  		c_in++;
		}
			  		TimerPort::incTimer(20);
	  		Thread::sleep(TimerPort::getTimer());
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
	
	while(1) {	
  		long size;
	  	const AppDataUnit* adu;
	  	do {
	  		adu = t->socket->getData(t->socket->getFirstTimestamp());
	  		if( NULL == adu )
	  			Thread::sleep(5);
	  	} while ( (NULL == adu) || ( (size = adu->getSize()) <= 0 ) );
	    
	   	sampleType *ptr = (sampleType*)adu->getData();

	  	TimerPort::incTimer(20);
	  	Thread::sleep(TimerPort::getTimer());
	   	
	   	snd_pcm_writei(t->playback_handle, ptr, size/2);
	   	c_out++;
    }
}

void TransceiverAlsa::openStream()
{
	int err;
	snd_pcm_info_t *info_in, *info_out;
	snd_output_t *log;
	
	snd_output_stdio_attach(&log, stderr, 0);
	
	// output stream
	
	snd_pcm_hw_params_t *hw_params;
	
	err = snd_pcm_open(&playback_handle, "default" , SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
	if(err < 0) cout << "Alsa error: cannot open device for playback : " << snd_strerror(err) << endl;
	snd_pcm_info_alloca(&info_out);
	err = snd_pcm_info(playback_handle, info_out);
	if(err < 0) cout << "Alsa error: cannot get info on playback device : " << snd_strerror(err) << endl;
	else {

	}
	
	err = snd_pcm_hw_params_malloc(&hw_params);
	if(err < 0) cout << "Alsa error: cannot allocate hw params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_any(playback_handle, hw_params);
	if(err < 0) cout << "Alsa error: cannot initialize hw params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err < 0) cout << "Alsa error: cannot set access type : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE);
	if(err < 0) cout << "Alsa error: cannot set sample format : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_channels(playback_handle, hw_params, 1);
	if(err < 0) cout << "Alsa error: cannot set channel count : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_rate(playback_handle, hw_params, sample_rate, 0);
	if(err < 0) cout << "Alsa error: cannot sample rate : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params(playback_handle, hw_params);
	if(err < 0) cout << "Alsa error: cannot hw parameters : " << snd_strerror(err) << endl;
	
	cout << "Playback device:" << endl;
	snd_pcm_hw_params_dump(hw_params, log);
	
	snd_pcm_hw_params_free(hw_params);
	
	snd_pcm_sw_params_t *sw_params_out;
	
	err = snd_pcm_sw_params_malloc(&sw_params_out);
	if(err < 0) cout << "Alsa error: cannot allocate sw params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params_current(playback_handle, sw_params_out);
	if(err < 0) cout << "Alsa error: cannot init sw params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params_set_avail_min(playback_handle, sw_params_out, frame_size);
	if(err < 0) cout << "Alsa error: cannot set avail min : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params(playback_handle, sw_params_out);
	if(err < 0) cout << "Alsa error: cannot set parameters : " << snd_strerror(err) << endl;
	err = snd_pcm_prepare(playback_handle);
	if(err < 0) cout << "Alsa error: cannot prepare audio interface for use : " << snd_strerror(err) << endl;
	
	snd_pcm_sw_params_dump(sw_params_out, log);
	
	snd_pcm_dump(playback_handle, log);
	
	// input stream
	
	err = snd_pcm_open(&capture_handle, "default" , SND_PCM_STREAM_CAPTURE, SND_PCM_NONBLOCK);
	if(err < 0) cout << "Alsa error: cannot open device for playback : " << snd_strerror(err) << endl;
	
	snd_pcm_info_alloca(&info_in);
	err = snd_pcm_info(capture_handle, info_in);
	if(err < 0) cout << "Alsa error: cannot get info on capture device : " << snd_strerror(err) << endl;
	else {
		cout << "Capture device:" << endl << 
		"\tdevice:" << snd_pcm_info_get_device(info_in) << endl <<
		"\tsubdevice:" << snd_pcm_info_get_subdevice(info_in) << endl <<
		"\tcard:" << snd_pcm_info_get_card(info_in) << endl <<
		"\tid:" << snd_pcm_info_get_id(info_in) << endl <<
		"\tname:" << snd_pcm_info_get_name(info_in) << endl <<
		"\tsubdevice_name:" << snd_pcm_info_get_subdevice_name(info_in) << endl;
	}
	
	err = snd_pcm_nonblock(capture_handle, 1);
	if(err < 0) cout << "Alsa error: cannot set nonblocking on capture device : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_malloc(&hw_params);
	if(err < 0) cout << "Alsa error: cannot allocate params structure : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_any(capture_handle, hw_params);
	if(err < 0) cout << "Alsa error: cannot initialize params : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	if(err < 0) cout << "Alsa error: cannot set access on capture device : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE);
	if(err < 0) cout << "Alsa error: cannot set format : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 1);
	if(err < 0) cout << "Alsa error: cannot set channel count : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params_set_rate(capture_handle, hw_params, sample_rate, 0);
	if(err < 0) cout << "Alsa error: cannot set sample rate : " << snd_strerror(err) << endl;
	snd_pcm_uframes_t bufsize = 1024;
	switch(sample_rate) {
		case 8000:
			bufsize >>= 2;
			break;
		case 16000:
			bufsize >>= 1;
			break;
		case 32000:
			bufsize = 1024;
			break;
		default:
			cout << "Frame rate " << sample_rate << " not supported" << endl;
	}
	err = snd_pcm_hw_params_set_buffer_size_near(capture_handle, hw_params, &bufsize);
	if(err < 0) cout << "Alsa error: cannot set buffer size near : " << snd_strerror(err) << endl;
	err = snd_pcm_hw_params(capture_handle, hw_params);
	if(err < 0) cout << "Alsa error: cannot set hw params : " << snd_strerror(err) << endl;
	
	cout << endl << endl << "Capture device" << endl;
	snd_pcm_hw_params_dump(hw_params, log);
	
	snd_pcm_hw_params_free(hw_params);
	
	snd_pcm_sw_params_t *sw_params_in;

	err = snd_pcm_sw_params_malloc(&sw_params_in);
	if(err < 0) cout << "Alsa error: cannot allocate sw params for capture device : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params_current(capture_handle, sw_params_in);
	if(err < 0) cout << "Alsa error: cannot initialize params : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params_set_avail_min(capture_handle, sw_params_in, bufsize/2);
	if(err < 0) cout << "Alsa error: cannot set avail mi : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params_set_stop_threshold(capture_handle, sw_params_in, bufsize*4);
	if(err < 0) cout << "Alsa error: cannot set stop threshold : " << snd_strerror(err) << endl;
	err = snd_pcm_sw_params(capture_handle, sw_params_in);
	if(err < 0) cout << "Alsa error: cannot set sw params : " << snd_strerror(err) << endl;
	err = snd_pcm_prepare(capture_handle);
	if(err < 0) cout << "Alsa error: cannot prepare capture device : " << snd_strerror(err) << endl;
	
	snd_pcm_sw_params_dump(sw_params_in, log);
	
	snd_pcm_dump(capture_handle, log);
} 

} /* namespace agh */
