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

#ifndef __TRANSCEIVERPA_H__INCLUDED__
#define __TRANSCEIVERPA_H__INCLUDED__

#include "device.h"
#include "aghrtpsession.h"
#include "transceiver.h"
#include "devicefactorypa.h"
#include <cc++/address.h>

using namespace std;
using namespace ost;

namespace agh {

typedef struct {
	sampleType *inputBuffer;
	sampleType *outputBuffer;
	bool outputReady;
	bool inputReady;
	AghRtpSession *socket;
	int packetCounter;
	sampleType ringBuffer[RING_BUFFER_SIZE];
	sampleType *ringBufferEnd;
	int ringBufferWriteIndex;
	int ringBufferReadIndex;
} CallbackData; 

class TransceiverPa;
	
class TransmitterCore : public Thread, public TimerPort {
	TransceiverPa* t;
	
public:
	TransmitterCore(TransceiverPa* tpa);
	~TransmitterCore();
	
	void run();
};

class ReceiverCore : public Thread, public TimerPort {
	TransceiverPa* t;
	
public:
	ReceiverCore(TransceiverPa* tpa);
	~ReceiverCore();
	
	void run();
};

class TransceiverPa : public ITransceiver {
private:

	friend class TransmitterCore;
	friend class ReceiverCore;

	DeviceFactoryPa* devMgr;
	const IDevice* inputDevice;
	const IDevice* outputDevice;
	
	IPV4Address localAddress;
	int localPort;
	IPV4Address remoteAddress;
	int remotePort;
	
	PaStream* inputStream;
	PaStream* outputStream;
	//PaStream* stream;
	CallbackData cData;
	AghRtpSession *socket;
	
	TransmitterCore *tCore;
	ReceiverCore *rCore;
	
	int framesPerBuffer;
	
	void openStream();
public: 
	TransceiverPa();
	~TransceiverPa();
	vector<IDevice*> getAvailableInputDevices() const;
	vector<IDevice*> getAvailableOutputDevices() const;
	int setInputDevice(const IDevice& dev);
	int setOutputDevice(const IDevice& dev);
	int setInputDevice(const int id);
	int setOutputDevice(const int id);
	int setCodec(int codec);
	int setLocalEndpoint(const IPV4Address& addr, int port);
	int setRemoteEndpoint(const IPV4Address& addr, int port);
	
	int start();
	int stop();
};

} /* namespace agh */

#endif