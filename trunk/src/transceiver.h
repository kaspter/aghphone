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

#ifndef __TRANSCEIVER_H__INCLUDED__
#define __TRANSCEIVER_H__INCLUDED__

#include <vector>
#include <cc++/address.h>
#include <string>

#include <portaudio.h>
#include <ccrtp/rtp.h>

using namespace std;
using namespace ost;

#define RING_BUFFER_SIZE	512

namespace agh {

#define SAMPLE_TYPE	paInt16
typedef short sampleType;

typedef struct {
	sampleType *inputBuffer;
	sampleType *outputBuffer;
	bool outputReady;
	bool inputReady;
	RTPSession *socket;
	int packetCounter;
	sampleType ringBuffer[RING_BUFFER_SIZE];
	sampleType *ringBufferEnd;
	int ringBufferWriteIndex;
	int ringBufferReadIndex;
	
} CallbackData; 


class IDevice {
public:
	virtual ~IDevice() {}
	virtual const string& getName() const = 0;
	virtual int getID() const = 0;
	virtual const string& getHostAPI() const = 0;

	virtual double getDefaultLowInputLatency() const = 0;
	virtual double getDefaultLowOutputLatency() const = 0;
	virtual double getDefaultHighInputLatency() const = 0;
	virtual double getDefaultHighOutputLatency() const = 0;
	virtual double getDefaultSampleRate() const = 0;
	virtual const vector<double>& getSupportedSampleRatesHalfDuplexInput() const = 0;
	virtual const vector<double>& getSupportedSampleRatesHalfDuplexOutput() const = 0;
	virtual const vector<double>& getSupportedSampleRatesFullDuplex() const = 0;

	virtual int getSupportedChannelCountOutput() const = 0;
	virtual int getSupportedChannelCountInput() const = 0;
};

class DevicePa : public IDevice {
private:
	string name;
	string hostAPI;
	int id;
	double defLowInputLat, defLowOutputLat, defHighInputLat, defHighOutputLat;
	double defSampleRate;
	vector<double> sampleRatesHalfDupInput, sampleRatesHalfDupOutput,
		sampleRatesFullDup;
	int channelCountOutput, channelCountInput;
public:
	DevicePa(int index);

	const string& getName() const { return (const string&)name; }
	int getID() const { return id; }
	const string& getHostAPI() const { return (const string&)hostAPI; }
	
	double getDefaultLowInputLatency() const { return defLowInputLat; }
	double getDefaultLowOutputLatency() const { return defLowOutputLat; }
	double getDefaultHighInputLatency() const { return defHighInputLat; }
	double getDefaultHighOutputLatency() const { return defHighOutputLat; }
	double getDefaultSampleRate() const { return defSampleRate; }
	const vector<double>& getSupportedSampleRatesHalfDuplexInput() const { return (const vector<double>&)sampleRatesHalfDupInput; }
	const vector<double>& getSupportedSampleRatesHalfDuplexOutput() const { return (const vector<double>&)sampleRatesHalfDupOutput; }
	const vector<double>& getSupportedSampleRatesFullDuplex() const { return (const vector<double>&)sampleRatesFullDup; }
	
	int getSupportedChannelCountOutput() const { return channelCountOutput; }
	int getSupportedChannelCountInput() const { return channelCountInput; }
};

class IDeviceFactory {
public:
	virtual ~IDeviceFactory() {}
	virtual int getDeviceCount() const = 0;
	virtual IDevice& getDevice(int index) const = 0;
	
	virtual IDevice& getDefaultInputDevice() const = 0;
	virtual IDevice& getDefaultOutputDevice() const = 0;
};

class DeviceFactoryPa : public IDeviceFactory {
	int deviceCount;
	vector<DevicePa*> devs;
public:
	DeviceFactoryPa();
	
	int getDeviceCount() const { return deviceCount; }
	IDevice& getDevice(int index) const { return (IDevice& )(*devs[index]); }
	
	IDevice& getDefaultInputDevice() const;
	IDevice& getDefaultOutputDevice() const;
};

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

class ITransceiver {
public:
	virtual ~ITransceiver() {}
	virtual vector<IDevice*> getAvailableInputDevices() const = 0;
	virtual vector<IDevice*> getAvailableOutputDevices() const = 0;
	virtual int setInputDevice(const IDevice& dev) = 0;
	virtual int setOutputDevice(const IDevice& dev) = 0;
	virtual int setCodec(int codec) = 0;
	virtual int setLocalEndpoint(const IPV4Address& addr, int port) = 0;
	virtual int setRemoteEndpoint(const IPV4Address& addr, int port) = 0;
	
	virtual int start() = 0;
	virtual int stop() = 0;
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
	RTPSession *socket;
	
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

#endif /* __TRANSCEIVER_H__INCLUDED__ */
