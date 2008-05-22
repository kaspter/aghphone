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
#include <ccrtp/rtp.h>

using namespace std;
using namespace ost;

namespace agh {

static int callback(  const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
 	                  const PaStreamCallbackTimeInfo* timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData )
{
	CallbackData *data = (CallbackData*)userData;

	(void) timeInfo;

	memcpy(data->inputBuffer, inputBuffer, framesPerBuffer);
	if( data->outputReady ) {
		memcpy(outputBuffer, data->outputBuffer, framesPerBuffer);
		data->outputReady = false;
	}

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
}

IDevice& DeviceFactoryPa::getDefaultInputDevice() const
{
	return getDevice(Pa_GetDefaultInputDevice());
}

IDevice& DeviceFactoryPa::getDefaultOutputDevice() const
{
	return getDevice(Pa_GetDefaultOutputDevice());
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
		
		tCore = NULL;
		cout << "Transceiver created successfuly" << endl;
	}
}

TransceiverPa::~TransceiverPa()
{
	if( devMgr)
		delete devMgr;
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

int TransceiverPa::setOutputDevice(const IDevice& dev)
{
	outputDevice = &dev;
	
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
		
	tCore = new TransceiverCore(this);
	tCore->start();
	
	cout << "Transceiver core started" << endl;
	
	return TransceiverStartResult::SUCCESS;
}

int TransceiverPa::stop()
{
	if( tCore )
		delete tCore;
	
	return 0;
}

TransceiverCore::TransceiverCore(TransceiverPa* tpa)
{
	t = tpa;
	
	cData.inputBuffer = NULL;
	cData.outputBuffer = NULL;
}

TransceiverCore::~TransceiverCore()
{
	terminate();
	
	Pa_CloseStream(t->stream);
	Pa_Terminate();     
	
	if( cData.inputBuffer )
		delete cData.inputBuffer;
	if( cData.outputBuffer )
		delete cData.outputBuffer;
}

void TransceiverCore::run()
{
	openStream();
	
	socket = new RTPSession( IPV4Host(t->localAddress.getAddress()), t->localPort );

	socket->setSchedulingTimeout( 10000 );
	//	  socket->setExpireTimeout(10000);
	
	
	if( !socket->addDestination( IPV4Host(t->remoteAddress.getAddress()), t->remotePort ) ) {
		/*
		 * TODO: Implement ccrtp connection failure
		 */
		cout << "CCRTP destination connection failure: " << IPV4Host(t->remoteAddress.getAddress()) << ":" << t->remotePort << endl;
		return;
	}
	
	socket->setPayloadFormat( StaticPayloadFormat( sptPCMU ) );

	socket->startRunning();
	
	setCancel(cancelImmediate);

/*
  	if( socket->RTPDataQueue::isActive() )
		cout << "active." << endl;
	else
	    cerr << "not active." << endl;
*/
	
	TimerPort::setTimer(20);
	
	int packetCounter = 0;
	
	for(int i=0;i<160;i++)
		cData.outputBuffer[i] = 0;
	
	cData.outputReady = true;
	
	while(1) {
		socket->putData(160*packetCounter,(const unsigned char *)cData.inputBuffer, 160);

  		long size;
	  	const AppDataUnit* adu;
	  	do {
	  		adu = socket->getData(socket->getFirstTimestamp());
	  		if( NULL == adu )
	  			Thread::sleep(5);
	  	} while ( (NULL == adu) || ( (size = adu->getSize()) == 0 ) );
	    
	    memcpy((void *)cData.outputBuffer, adu->getData(), 160);
		cData.outputReady = true;

	    packetCounter++;
	    printf("timestamp: %d\n", packetCounter*160); fflush(stdout); 
	    Thread::sleep(TimerPort::getTimer());
	    TimerPort::incTimer(20);
    }
}

void TransceiverCore::openStream()
{
	PaStreamParameters inputParameters, outputParameters;
	
	inputParameters.device = t->inputDevice->getID(); /* default input device */
  	inputParameters.channelCount = 1;                    /* stereo input */
	inputParameters.sampleFormat = paInt8;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;
	//cout << "input device conf" << inputParameters.device << endl;	  
    
    outputParameters.device = t->outputDevice->getID(); /* default input device */
  	outputParameters.channelCount = 1;                    /* stereo input */
	outputParameters.sampleFormat = paInt8;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	//cout << "output device conf" << outputParameters.device << endl;
	
	cData.inputBuffer = new char[160];
	cData.outputBuffer = new char[160];
	
  	/* Record some audio. -------------------------------------------- */
  	PaError err = Pa_OpenStream(
       &(t->stream),
       &inputParameters,
       &outputParameters,
   	   8000, // sample rate
   	   160, // framesPerBuffer
   	   paClipOff,      /* we won't output out of range samples so don't bother clipping them */
       callback,
       &cData );

	if(err != paNoError) {
		/*
		 * TODO: Implement logging of stream opening failure
		 */
		cout << Pa_GetErrorText(err) << endl;
		return;
	}

	err = Pa_StartStream(t->stream);

	if(err != paNoError) {
		/*
		 * TODO: Implement logging of stream starting failure
		 */
		cout << Pa_GetErrorText(err) << endl;
		return;
	}	
} 

} /* namespace agh */
