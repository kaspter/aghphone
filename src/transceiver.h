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
#include <map>

#include <portaudio.h>
#include <alsa/asoundlib.h>
#include <ccrtp/rtp.h>

using namespace std;
using namespace ost;

#define RING_BUFFER_SIZE	480


namespace agh {

#define SAMPLE_TYPE	paInt16
typedef short sampleType;

class AghRtpSession : public SymmetricRTPSession {
public:
	~AghRtpSession() {}
	 
	AghRtpSession(const InetHostAddress &host);
	AghRtpSession(const InetHostAddress &host, unsigned short port);
	uint32 getLastTimestamp(const SyncSource *src=NULL) const;
};

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

class DeviceAlsa : public IDevice {
private:
	string name;
	const vector<double> sampleRates;
public:
	DeviceAlsa(string name) { this->name = name; }

	const string& getName() const { return (const string&)name; }
	int getID() const { return 0; }
	const string& getHostAPI() const { return ""; }
	
	double getDefaultLowInputLatency() const { return 0.0; }
	double getDefaultLowOutputLatency() const { return 0.0; }
	double getDefaultHighInputLatency() const { return 0.0; }
	double getDefaultHighOutputLatency() const { return 0.0; }
	double getDefaultSampleRate() const { return 0.0; }
	const vector<double>& getSupportedSampleRatesHalfDuplexInput() const { return (const vector<double>&)sampleRates; }
	const vector<double>& getSupportedSampleRatesHalfDuplexOutput() const { return (const vector<double>&)sampleRates; }
	const vector<double>& getSupportedSampleRatesFullDuplex() const { return (const vector<double>&)sampleRates; }
	
	int getSupportedChannelCountOutput() const { return 0; }
	int getSupportedChannelCountInput() const { return 0; }
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

class DeviceFactoryAlsa : public IDeviceFactory {
	IDevice *defaultDevice;
	vector<DeviceAlsa*> devs;
	map<string, DeviceAlsa*> devmap;
public:
	DeviceFactoryAlsa()
	{
		DeviceAlsa *dev = new DeviceAlsa("default");
		devs.push_back(dev);
		devmap["default"] = dev;
		defaultDevice = dev;
	}
	
	int getDeviceCount() const { return devs.size(); }
	IDevice& getDevice(int index) const { return (IDevice& )(*devs[index]); }
	IDevice& getDevice(const string name) { 
		map<string, DeviceAlsa*>::iterator iter; 
		if((iter = devmap.find(name)) != devmap.end())
			return *((*iter).second);
		 else {
		 	DeviceAlsa *dev = new DeviceAlsa(name);
		 	devmap[name] = dev;
		 	devs.push_back(dev);
		 	return *dev;
		 }
	}
	
	IDevice& getDefaultInputDevice() const { return *defaultDevice; }
	IDevice& getDefaultOutputDevice() const { return *defaultDevice; }
};

class TransceiverPa;
class TransceiverAlsa;

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

class TransmitterAlsaCore : public Thread, public TimerPort {
	TransceiverAlsa* t;
	
public:
	TransmitterAlsaCore(TransceiverAlsa* tpa);
	~TransmitterAlsaCore();
	
	void run();
};

class ReceiverAlsaCore : public Thread, public TimerPort {
	TransceiverAlsa* t;
	
public:
	ReceiverAlsaCore(TransceiverAlsa* tpa);
	~ReceiverAlsaCore();
	
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

class TransceiverAlsa : public ITransceiver {
private:

	friend class TransmitterAlsaCore;
	friend class ReceiverAlsaCore;

	DeviceFactoryAlsa* devMgr;
	const IDevice* inputDevice;
	const IDevice* outputDevice;
	
	IPV4Address localAddress;
	int localPort;
	IPV4Address remoteAddress;
	int remotePort;
	
	CallbackData cData;
	AghRtpSession *socket;
	
	TransmitterAlsaCore *tCore;
	ReceiverAlsaCore *rCore;
	
	int framesPerBuffer;
	int sample_rate;
	
	snd_pcm_t *playback_handle;
	snd_pcm_t *capture_handle;
	snd_pcm_sframes_t delayNow;
	snd_pcm_state_t state;
	
	float delay, minDelay, maxDelay, stretch, tempoChane, fdel;
	bool adr, ringing;
	int readyFrames, prebuffer, preframes, prepackets, frame_size;
	short *shortBuffer;
	bool working;
	sampleType sampleBuffer[2048];
	short *samples;
	float *audioBuffer;
	
	struct timeval czas_start;
	
	
	long inputBufferSize;
	long inputBufferCursor;
	long inputBufferCursor2;
	long inputBufferReady;
	sampleType inputBuffer[4096];
	long outputBufferSize;
	long outputBufferCursor;
	long outputBufferCursor2;
	long outputBufferReady;
	sampleType outputBuffer[4096];
	
	void openStream();
	snd_pcm_t* alsa_set_params(snd_pcm_t *pcm_handle, int rw);
	bool alsa_can_read(snd_pcm_t *dev, int frames);
	void alsa_fill_w(snd_pcm_t *pcm_handle);
	int alsa_read(snd_pcm_t *handle, unsigned char* buf, int nsamples);
	int alsa_write(snd_pcm_t *handle, unsigned char* buf, int nsamples);
	
public: 
	TransceiverAlsa();
	~TransceiverAlsa();
	vector<IDevice*> getAvailableInputDevices() const;
	vector<IDevice*> getAvailableOutputDevices() const;
	int setInputDevice(const IDevice& dev);
	int setOutputDevice(const IDevice& dev);
	int setInputDevice(const int id);
	int setOutputDevice(const int id);
	int setInputDevice(const string name) { inputDevice = &(devMgr->getDevice(name)); return 0; }
	int setOutputDevice(const string name) { outputDevice = &(devMgr->getDevice(name)); return 0; }
	int setCodec(int codec);
	int setLocalEndpoint(const IPV4Address& addr, int port);
	int setRemoteEndpoint(const IPV4Address& addr, int port);
	
	int start();
	int stop();
	
	void initTime();
	void printTime();
};

} /* namespace agh */

#endif /* __TRANSCEIVER_H__INCLUDED__ */
