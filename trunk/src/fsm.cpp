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

/** TODO:
 *  - remove ugly "clog <<" debug method
 *  - add some logging
 *  - ice exception handling
 *  - mutexes
 */

#include <iostream>
#include <map>
#include <Ice/Ice.h>
#include <cc++/address.h>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <iface.h>
#include "master.h"
#include "restypes.h"
#include "globals.h"
#include "tools.h"
#include "master.h"
#include "transceiver.h"

using namespace std;
using namespace agh;
using namespace ost;

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace agh {

LoggerPtr logger(Logger::getLogger("MyApp"));

class Terminal : public ISlave, public IMaster {
protected:
	const static string adapterName;
	const static string remoteTerminalName;
	const static int defaultIcePort;
	const static int defaultRtpPort;

	enum State {
		DISCONNECTED,

		PASSIVE_CONNECTED,
		PASSIVE_OPERATIONAL,

		ACTIVE_CONNECTED,
		ACTIVE_OPERATIONAL
	};

	int codec;

	int remotePort;
	int localPort;

	int remoteIcePort;
	int localIcePort;

	IPV4Address *localAddr;
	IPV4Address *remoteAddr;

	State currentState;

	Ice::CommunicatorPtr ic;
	Ice::ObjectAdapterPtr adapter;

	ISlavePrx remoteTerminal;

	ICallback* localCallback;
	ITransceiver* transceiver;

public:
	Terminal(int lIcePort = defaultIcePort, int rIcePort = defaultIcePort);
	virtual ~Terminal();

	virtual bool isConnected() const;
	virtual int setLocalPort(int port);
	virtual int getLocalPort() const;
	virtual int getDestinationPort() const;
	virtual const IPV4Address* getRemoteHost() const;
	virtual const IPV4Address* getLocalHost() const;
	virtual int connect(const ost::IPV4Address&, int port);
	virtual int disconnect();
	virtual int startTransmission();
	virtual int registerCallback(agh::ICallback* callback);
	virtual int unregisterCallback(int id);
	virtual int setTransceiver(agh::ITransceiver* trans);
	virtual int unsetTransceiver();

	virtual int remoteConnect(const Ice::Current& cur);
	virtual int remoteDisconnect(int reason, const Ice::Current& cur);
	virtual int remotePing(const Ice::Current& cur);
	virtual prefferedCodecs remoteGetPrefferedOutgoingCodec(
			const Ice::Current& cur);
	virtual prefferedCodecs remoteGetPrefferedIncomingCodec(
			const Ice::Current& cur);
	virtual int remoteSetOutgoingCodec(Ice::Int, const Ice::Current& cur);
	virtual int remoteResetOutgoingCodec(Ice::Int, const Ice::Current& cur);
	virtual int remoteSetDestinationPort(Ice::Int, const Ice::Current& cur);
	virtual int remoteGetDestinationPort(int port, const Ice::Current& cur);
	virtual int remoteGetSourcePort(const Ice::Current& cur);
	virtual int remoteStartTransmission(const Ice::Current& cur);
};

const string Terminal::adapterName("AGHPhoneAdapter");
const string Terminal::remoteTerminalName("Slave");
const int Terminal::defaultIcePort = 24474;
const int Terminal::defaultRtpPort = 5004;

Terminal::Terminal(int lIcePort, int rIcePort) :
	remotePort(defaultRtpPort), localPort(defaultRtpPort),
			remoteIcePort(rIcePort), localIcePort(lIcePort), localAddr(0),
			remoteAddr(0), currentState(DISCONNECTED), ic(0), adapter(0),
			remoteTerminal(0), localCallback(0), transceiver(0),
			codec(AudioCodec::PCMU) {

	if ((remoteIcePort < 1024) || (remoteIcePort > 32768))
		remoteIcePort = defaultIcePort;
	if ((localIcePort < 1024) || (localIcePort > 32768))
		localIcePort = defaultIcePort;

	ic = Ice::initialize();
	stringstream iceEndpoint;
	iceEndpoint << "default -p " << localIcePort;
	adapter = ic->createObjectAdapterWithEndpoints(adapterName,
			iceEndpoint.str());
	ISlavePtr localTerminal = this;
	adapter->add(localTerminal, ic->stringToIdentity(remoteTerminalName));
	adapter->activate();

}

Terminal::~Terminal() {
	if (ic)
		ic->destroy();
	if (localAddr)
		delete localAddr;
	if (remoteAddr)
		delete remoteAddr;
}

bool Terminal::isConnected() const {
	return currentState != DISCONNECTED;
}

int Terminal::setLocalPort(int port) {
	if ((port < 1024) || (port > 32768)) {
		return 0;
	} else {
		localPort = port;
		return 0;
	}
}

int Terminal::getLocalPort() const {
	return localPort;
}

int Terminal::getDestinationPort() const {
	return remotePort;
}

const IPV4Address* Terminal::getRemoteHost() const {
	return remoteAddr;
}

const IPV4Address* Terminal::getLocalHost() const {
	return localAddr;
}

//TODO: Implement
int Terminal::connect(const IPV4Address& addr, int port) {
	stringstream a;
	a << addr;
	LOG4CXX_DEBUG(logger, string("Terminal::connect(") << a.str() << ", " << port << ")");

	if (currentState != DISCONNECTED) {
		LOG4CXX_INFO(logger, "Already connected");
		return ConnectResult::ALREADY_CONNECTED;
	}

	if (!addr.isInetAddress()) {
		LOG4CXX_ERROR(logger, "Incorrect address: " << a.str());
		return ConnectResult::INVALID_HOST;
	}

	if ((port < 1024) || (port > 32768)) {
		LOG4CXX_ERROR(logger, "Incorrect or out of range port number: " << port);
		return ConnectResult::INVALID_HOST;
	}

	if (remoteAddr)
		delete remoteAddr;
	remoteAddr = new IPV4Address(addr);
	remoteIcePort = port;

	stringstream remoteEndpoint;
	remoteEndpoint << remoteTerminalName << ":default"; 
	remoteEndpoint << " -h " << remoteAddr->getAddress();
	remoteEndpoint << " -p " << remoteIcePort;

	LOG4CXX_DEBUG(logger, "Remote Endpoint: \"" << remoteEndpoint.str() << "\"");

	LOG4CXX_DEBUG(logger, "Accessing remote object");

	Ice::ObjectPrx base = ic->stringToProxy(remoteEndpoint.str());
	remoteTerminal = ISlavePrx::checkedCast(base);

	LOG4CXX_DEBUG(logger, "Successfully received remote object");

	LOG4CXX_DEBUG(logger, "Calling remote site");
	int res = remoteTerminal->remoteConnect();

	switch (res) {
	case RequestConnectResult::BUSY:
		LOG4CXX_DEBUG(logger, "Remote site busy");
		return ConnectResult::BUSY;
	case RequestConnectResult::REJECTED:
		LOG4CXX_DEBUG(logger, "Remote site rejected connection");
		return ConnectResult::REJECTED;
	case RequestConnectResult::INTERNAL_ERROR:
		LOG4CXX_ERROR(logger, "Internal Error");
		return ConnectResult::INTERNAL_ERROR;
	}

	if (res != RequestConnectResult::SUCCESS) {
		LOG4CXX_FATAL(logger, "General error");
		return ConnectResult::OTHER;
	}

	LOG4CXX_DEBUG(logger, "Transition to ACTIVE_CONNECTED state");
	currentState = ACTIVE_CONNECTED;

	// TODO: Add connection monitor (heartbeat)
}

int Terminal::startTransmission() {
	LOG4CXX_DEBUG(logger, "Terminal::startTransmission()");
	if (transceiver) {
		if (currentState != ACTIVE_CONNECTED) {
			LOG4CXX_ERROR(logger, "Not connected or transmission already set");
			return -1;
		}
		//TODO: Codec negotiation
		transceiver->setCodec(AudioCodec::PCMU); //uLaw

		// TODO: How the hell master is able to know its nic's address
		// transceiver->setLocalEndpoint()
		transceiver->setLocalEndpoint(*localAddr, localPort);
		transceiver->setRemoteEndpoint(*remoteAddr, remotePort);

		int res = transceiver->start();

		// TODO: switch to smarter error handling mechanism (like other methods)
		if (res != 0) {
			LOG4CXX_ERROR(logger, "Cannot start transmission");
			return res;
		}

		res = remoteTerminal->remoteStartTransmission();

		//TODO: change error mechanism
		if (res != 0) {
			LOG4CXX_ERROR(logger, "Cannot start remote transmission");
			return res;
		}

		LOG4CXX_DEBUG(logger, "Transition to ACTIVE_OPERATIONAL state");
		currentState = ACTIVE_OPERATIONAL;

		return 0; //TODO: change error mechanism
	}
	LOG4CXX_DEBUG(logger, "No transceiver");
	return -1; //TODO: change error mechanism
}

int Terminal::disconnect() {
	LOG4CXX_DEBUG(logger, "Terminal::disconnect()");
	if (currentState != DISCONNECTED) {
		// TODO: stop trasmission (Transceiver component needed first
		LOG4CXX_DEBUG(logger, "Transition to DISCONNECTED state");
		currentState == DISCONNECTED;
	}
	return DisconnectResult::SUCCESS;
}

// TODO: switch to smarter mechanism?
int Terminal::registerCallback(agh::ICallback* callback) {
	localCallback = callback;
}

int Terminal::unregisterCallback(int s) {
	localCallback = 0;
}

int Terminal::setTransceiver(agh::ITransceiver* trans) {
	transceiver = trans;
}

int Terminal::unsetTransceiver() {
	transceiver = 0;
}

int Terminal::remoteConnect(const Ice::Current& cur) {
	LOG4CXX_DEBUG(logger, "Terminal::remoteConnect()");
	if (currentState == DISCONNECTED) {
		if (localCallback && !localCallback->onIncomingCall(*remoteAddr))
			return RequestConnectResult::REJECTED;
		currentState = PASSIVE_CONNECTED;
		LOG4CXX_DEBUG(logger, "Transition to PASSIVE_CONNECTED state");
		if (remoteAddr)
			delete remoteAddr;
		if (localAddr)
			delete localAddr;
		remoteAddr = new IPV4Address(getRemoteAddressFromConnection(cur.con));
		localAddr = new IPV4Address(getLocalAddressFromConnection(cur.con));
		// TODO: Remote Callback register (add to ICE iterface!!)
		return RequestConnectResult::SUCCESS;
	} else {
		return RequestConnectResult::BUSY;
	}
}

int Terminal::remoteDisconnect(int reason, const Ice::Current& cur) {
	LOG4CXX_DEBUG(logger, "Terminal::remoteDisconnect(" << reason << ")");
	if (currentState != DISCONNECTED) {
		LOG4CXX_DEBUG(logger, "Transition to DISCONNECTED state");
	}
	return DisconnectResult::SUCCESS;
}

int Terminal::remotePing(const Ice::Current& cur) {
	//TODO: To be implemented
}

prefferedCodecs Terminal::remoteGetPrefferedOutgoingCodec(
		const Ice::Current& cur) {
	//TODO: To be implemented
	vector<int> codecs;
	codecs.push_back(AudioCodec::PCMU);
	return codecs;
}

prefferedCodecs Terminal::remoteGetPrefferedIncomingCodec(
		const Ice::Current& cur) {
	//TODO: To be implemented
	vector<int> codecs;
	codecs.push_back(AudioCodec::PCMU);
	return codecs;
}

int Terminal::remoteSetOutgoingCodec(int codec, const Ice::Current& cur) {
	this->codec = codec;
}

int Terminal::remoteResetOutgoingCodec(int codec, const Ice::Current& cur) {
	//TODO: To be implemented
}

int Terminal::remoteSetDestinationPort(int port, const Ice::Current& cur) {
	if (port < 1024 || port > 32768)port = defaultRtpPort;
	remotePort = port;
	return port;
}

int Terminal::remoteGetDestinationPort(int port, const Ice::Current& cur) {
	return remotePort;
}

int Terminal::remoteGetSourcePort(const Ice::Current& cur) {
	return localPort;
}

int Terminal::remoteStartTransmission(const Ice::Current& cur) {
	LOG4CXX_DEBUG(logger, "Terminal::remoteStartTransmission()");
	if (transceiver) {
		transceiver->setCodec(codec);

		transceiver->setLocalEndpoint(*localAddr, localPort);
		transceiver->setRemoteEndpoint(*remoteAddr, remotePort);

		int res = transceiver->start();

		// TODO: switch to smarter error handling mechanism (like other methods)
		if (res != 0) {
			LOG4CXX_ERROR(logger, "Cannot start transmission");
			return res;
		}

		if (currentState != PASSIVE_CONNECTED) {
			LOG4CXX_ERROR(logger, "Not connected or transmission already set");
			return -1;
		}

		LOG4CXX_DEBUG(logger, "Transition to PASSIVE_OPERATIONAL state");
		currentState = PASSIVE_OPERATIONAL;
		return 0; //TODO: change error mechanism
	}
	LOG4CXX_DEBUG(logger, "No transceiver");
	return -1; //TODO: change error mechanism
}

/** For TEST ONLY purposes there's possibility to set signalling port
 *  Remove the 'feature' from final version
 */
/*
 class AppComponent : public ISlave {
 protected:

 enum State {
 DISCONNECTED,

 PASSIVE_CONNECTED,
 PASSIVE_NEGOTIATED,
 PASSIVE_OPERATIONAL,

 ACTIVE_CONNECTED,
 ACTIVE_OPERATIONAL,

 INITIAL = DISCONNECTED
 };

 int remotePort;
 int localPort;
 int icePort;
 int remoteIcePort;

 State currentState;

 IPV4Address *remoteHost;

 Ice::CommunicatorPtr ic;
 Ice::ObjectAdapterPtr adapter;

 //Remote object
 ISlavePrx remoteComponent;

 public:

 AppComponent(int bindPort);
 ~AppComponent(); 

 /// methods to be remotly invoked for passive connection
 virtual int requestConnect(const Ice::Current&);
 virtual CodecsMap getAvailableCodecs(const Ice::Current&);
 virtual int setCodec(int codec, const Ice::Current&);
 virtual int resetCodec(int codec, const Ice::Current&);
 virtual int setDestinationPort(int port, const Ice::Current&);
 virtual int getSourcePort(const Ice::Current&);
 virtual int startTransmission(const Ice::Current&);
 virtual int disconnect(int reason, const Ice::Current&);
 virtual void setCallback(const ISlaveCallbackPrx& callback,
 const Ice::Current&);

 virtual ISlaveCallbackPrx getCallback(const Ice::Current&);

 /// methods to be locally invoked for active connection
 virtual int connect(const IPV4Address& host, int port);
 virtual void setLocalPort(int port);
 virtual int negotiate();

 /// general methods
 };

 // might throws Ice::Exception 
 AppComponent::AppComponent(int bindPort) :
 currentState(INITIAL), ic(0), adapter(0), remoteComponent(0),
 remoteHost(0), localPort(defaultRtpPort), remotePort(0),
 icePort(bindPort) {
 ic = Ice::initialize();

 if ((icePort < 1024) || (icePort > 32768)) {
 icePort = defaultIcePort;
 }

 stringstream iceEndpoint;
 iceEndpoint << "default -p " << bindPort;
 adapter = ic->createObjectAdapterWithEndpoints(adapterName,
 iceEndpoint.str());
 ISlavePtr component = this;
 adapter->add(component, ic->stringToIdentity(componentName));
 adapter->activate();
 }

 AppComponent::~AppComponent() {
 if (ic) {
 ic->destroy();
 }
 }

 int AppComponent::requestConnect(const Ice::Current& current) {
 clog << "requestConnect" << endl;
 if (currentState == DISCONNECTED) {
 currentState = PASSIVE_CONNECTED;
 // TODO: Callback register

 } else {
 //return ALREADY_CONNECTED;
 }

 getHostFromConnection(current.con);
 }

 CodecsMap AppComponent::getAvailableCodecs(const Ice::Current&) {

 }

 int AppComponent::setCodec(int codec, const Ice::Current&) {

 }

 int AppComponent::resetCodec(int codec, const Ice::Current&) {

 }

 int AppComponent::setDestinationPort(int port, const Ice::Current&) {
 if ((port < 1024) || (port > 32768)) {
 remotePort = defaultRtpPort;
 return SetDestinationPortResult::OUT_OF_RANGE;
 } else {
 remotePort = port;
 return SetCodecResult::SUCCESS;
 }
 }

 int AppComponent::getSourcePort(const Ice::Current&) {

 }

 int AppComponent::startTransmission(const Ice::Current&) {

 }

 int AppComponent::disconnect(int reason, const Ice::Current&) {

 }

 void AppComponent::setCallback(const ISlaveCallbackPrx& callback,
 const Ice::Current&) {

 }

 ISlaveCallbackPrx AppComponent::getCallback(const Ice::Current&) {

 }

 int AppComponent::connect(const IPV4Address& addr, int port = defaultRtpPort) {
 clog << "connect" << endl;
 int res;
 
 if (!addr.isInetAddress()) {
 return ConnectResult::INVALID_HOST;
 }

 if (currentState != DISCONNECTED) {
 return ConnectResult::ALREADY_CONNECTED;
 } else {
 safeDelete(remoteHost);
 remoteHost = new IPV4Host(addr.getAddress());

 if ((port < 1024) || (port > 32768)) {
 port = defaultIcePort;
 }
 remoteIcePort = port;

 stringstream remoteEndpoint;
 remoteEndpoint << componentName << ":default";
 remoteEndpoint << " -h " << remoteHost->getAddress();
 remoteEndpoint << " -p " << remoteIcePort;

 cout << remoteEndpoint.str() << endl;

 Ice::ObjectPrx base = ic->stringToProxy(remoteEndpoint.str());
 remoteComponent = ISlavePrx::checkedCast(base);

 res = remoteComponent->requestConnect();

 if (res != RequestConnectResult::SUCCESS) {
 switch (res) {
 case RequestConnectResult::INTERNAL_ERROR:
 return ConnectResult::INTERNAL_ERROR;
 break;
 case RequestConnectResult::NOT_IMPLEMENED_YET:
 return ConnectResult::NOT_IMPLEMENTED_YET;
 break;
 case RequestConnectResult::OTHER:
 return ConnectResult::OTHER;
 break;
 case RequestConnectResult::REJECTED:
 return ConnectResult::REJECTED;
 break;
 case RequestConnectResult::BUSY:
 return ConnectResult::BUSY;
 break;
 default:
 return ConnectResult::INTERNAL_ERROR;
 break;
 }
 }
 
 res = remoteComponent->setDestinationPort(localPort);
 
 if (res != SetDestinationPortResult::SUCCESS) {
 switch (res) {
 case SetDestinationPortResult::INTERNAL_ERROR:
 return ConnectResult::INTERNAL_ERROR;
 break;
 case SetDestinationPortResult::OTHER:
 return ConnectResult::OTHER;
 break;
 case SetDestinationPortResult::NOT_IMPLEMENTED_YET:
 return ConnectResult::NOT_IMPLEMENTED_YET;
 break;
 case SetDestinationPortResult::OUT_OF_RANGE:
 return ConnectResult::OTHER;
 break;
 default:
 return ConnectResult::INTERNAL_ERROR;
 break;
 }
 }
 
 currentState = ACTIVE_CONNECTED;
 
 /// TODO:
 //  codecs negotiating.. and setting the best one
 int bestCodec = AudioCodec::PCMU;
 res = remoteComponent->setCodec(bestCodec);
 
 if (res != SetCodecResult::SUCCESS) {
 switch (res) {
 case SetCodecResult::INTERNAL_ERROR:
 return ConnectResult::INTERNAL_ERROR;
 break;
 case SetCodecResult::NOT_IMPLEMENTED_YET:
 return ConnectResult::INTERNAL_ERROR;
 break;
 }
 }
 
 
 /// TODO:
 //  start sending RTP data;
 
 // start sending our rtp data
 
 res = remoteComponent->startTransmission();
 currentState = ACTIVE_OPERATIONAL;
 return ConnectResult::SUCCESS;
 }
 }

 // TODO: Implement
 int AppComponent::negotiate() {
 if (!remoteComponent) {
 return -1;
 }

 if (currentState != ACTIVE_CONNECTED) {
 // TODO:
 return -2;
 }

 //TODO:
 map<int, int> codecs = remoteComponent->getAvailableCodecs();
 int res1 = remoteComponent->setCodec(0);
 int res2 = remoteComponent->setDestinationPort(8888);
 int res3 = remoteComponent->getSourcePort();
 }

 void AppComponent::setLocalPort(int port) {
 if ((port < 1024) || (port > 32768)) {
 port = defaultRtpPort;
 }

 localPort = defaultRtpPort;
 }

 */

} /* namespace agh */

int main(int argc, char *argv[]) {
	try {
		// Set up a simple configuration that logs on the console.
		BasicConfigurator::configure();
	} catch(log4cxx::helpers::Exception& e) {
		clog << e.what() << endl;
	}

	int port;

	cout << audioCodecChannels[AudioCodec::L16_STEREO] << endl;
	cout << audioCodecChannels[AudioCodec::MPA] << endl;

	cout << audioCodecClockRate[AudioCodec::DVI4_22050] << endl;
	cout << audioCodecClockRate[AudioCodec::MPA] << endl;

	if (argc > 1) {
		// slave test
		port = 8347;
	} else {
		// master test
		port = 8348;
	}
	Terminal *app = new Terminal(port);

	if (argc > 1) {
		app->connect("localhost", 8348);
		app->startTransmission();
	} else {

	}

	LOG4CXX_DEBUG(logger, "Ala ma kota");

	sleep(6000);

}

