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
#include <IceUtil/IceUtil.h>
#include <cc++/address.h>
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/helpers/exception.h>



#include "iface.h"
#include "restypes.h"
#include "globals.h"
#include "terminal.h"
#include "states.h"
#include "tools.h"

using namespace std;
using namespace agh;
using namespace ost;

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace agh {

LoggerPtr logger(Logger::getLogger("MyApp"));

const string Terminal::adapterName("AGHPhoneAdapter");
const string Terminal::adapterCallbackName("AGHPhoneCallbackAdapter");
const string Terminal::remoteTerminalName("Slave");
const int Terminal::defaultIcePort = 24474;
const int Terminal::defaultRtpPort = 5004;

Terminal::Terminal(int lIcePort, int rIcePort) :
	remotePort(defaultRtpPort), localPort(defaultRtpPort),
			remoteIcePort(rIcePort), localIcePort(lIcePort), localAddr(0),
			remoteAddr(0), currentState(States::DISCONNECTED), ic(0), adapter(0),
			remoteTerminal(0), localCallback(0), transceiver(0),
			codec(AudioCodec::PCMU) {
	
	cout << "Constructor" << endl;
	
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
	
	//adapter->deactivate();
	//adapter->destroy();
	//ic->destroy();
	
	if (localAddr) {
		delete localAddr;
	}
	if (remoteAddr) {
		delete remoteAddr;
	}
}

bool Terminal::isConnected() const {
	return currentState != States::DISCONNECTED;
}

void Terminal::setLocalRtpPort(int port) {
	if ((port < 1024) || (port > 32768)) {
	} else {
		localPort = port;
	}
}

int Terminal::getLocalRtpPort() const {
	return localPort;
}

int Terminal::getDestinationRtpPort() const {
	return remotePort;
}

const IPV4Address* Terminal::getRemoteHost() const {
	return remoteAddr;
}

const IPV4Address* Terminal::getLocalHost() const {
	return localAddr;
}

//TODO: Implement
void Terminal::connect(const IPV4Address& addr, int port) {
	stringstream a;
	a << addr;
	LOG4CXX_DEBUG(logger, string("Terminal::connect(") << a.str() << ", " << port << ")");
	
	if (currentState != States::DISCONNECTED) {
		LOG4CXX_INFO(logger, "Already connected");
		throw TerminalBusyException();
	}
	
	if (!addr.isInetAddress()) {
		LOG4CXX_ERROR(logger, "Incorrect address: " << a.str());
		//TODO: another Exception
		throw VoipException();
	}
	
	if ((port < 1024) || (port > 32768)) {
		LOG4CXX_ERROR(logger, "Incorrect or out of range port number: " << port);
		//TODO: Another Exception
		throw VoipException();
	}
	
	if (remoteAddr)
		delete remoteAddr;
	remoteAddr = new IPV4Address(addr);
	remoteIcePort = port;
	localAddr = new IPV4Address("0.0.0.0");
	
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
	//TODO: Do smth w params
	CallParameters params;
	
	masterCallbackPtr = new MasterCallbackImpl((IMaster*) this);
	Ice::ObjectAdapterPtr tmpAdapter;
	tmpAdapter = ic->createObjectAdapter("");
	Ice::Identity tmpIdentity;
	tmpIdentity.name = IceUtil::generateUUID();
	tmpIdentity.category = "";
	
	tmpAdapter->add(masterCallbackPtr, tmpIdentity);
	tmpAdapter->activate();
	remoteTerminal->ice_getConnection()->setAdapter(tmpAdapter);
	
	this->changeState(States::ACTIVE_CONNECTED);
	remoteTerminal->remoteTryConnect(params, tmpIdentity);
	
	// change state
	cout << "AAAAAAAAAAAAAAAAAAAAAA\n";
	

	
}

void Terminal::changeState(int newState) {
	stringstream a;
	LOG4CXX_DEBUG(logger, "Terminal::changeState()");
	
	if (this->localCallback != 0) {
			// TODO inform UI, UI needs to be implemented first
			localCallback->onStateTransition(currentState, newState, *localAddr);
		}
	a << string("Terminal::changeState() prev: ") << this->currentState << " new: " << newState;
	LOG4CXX_DEBUG(logger, a.str());
	this->currentState = newState;
}

int Terminal::startTransmission() {
	LOG4CXX_DEBUG(logger, "Terminal::startTransmission()");
	if (transceiver) {
		if (currentState != States::ACTIVE_CONNECTED) {
			LOG4CXX_ERROR(logger, "Not connected or transmission already set");
			return -1;
		}
		//TODO: Codec negotiation
		transceiver->setCodec(AudioCodec::PCMU); //uLaw

		// TODO: How the hell master is able to know its nic's address
		// transceiver->setLocalEndpoint()
		transceiver->setLocalEndpoint(*localAddr, localPort);
		transceiver->setRemoteEndpoint(*remoteAddr, remotePort);

		int res = 0;
		//int res = transceiver->start();
		cout << "TRANSCEIVER STARTED";

		// TODO: switch to smarter error handling mechanism (like other methods)
		if (res != 0) {
			LOG4CXX_ERROR(logger, "Cannot start transmission");
			return res;
		}

		//res = remoteTerminal->remoteStartTransmission();

		//TODO: change error mechanism
		if (res != 0) {
			LOG4CXX_ERROR(logger, "Cannot start remote transmission");
			return res;
		}

		LOG4CXX_DEBUG(logger, "Transition to ACTIVE_OPERATIONAL state");
		changeState(States::ACTIVE_OPERATIONAL);

		return 0; //TODO: change error mechanism
	}
	LOG4CXX_DEBUG(logger, "No transceiver");
	return -1; //TODO: change error mechanism
}

void Terminal::disengage() {
	LOG4CXX_DEBUG(logger, "Terminal::disconnect()");
	if (currentState != States::DISCONNECTED) {
		// TODO: stop trasmission (Transceiver component needed first
		LOG4CXX_DEBUG(logger, "Transition to DISCONNECTED state");
		currentState == States::DISCONNECTED;
	}
}

void Terminal::registerCallback(agh::IUICallback* callback) {
	localCallback = callback;
}

void Terminal::unregisterCallback() {
	localCallback = 0;
}

void Terminal::setTransceiver(agh::ITransceiver* trans) {
	transceiver = trans;
}

void Terminal::unsetTransceiver() {
	transceiver = 0;
}

TerminalCapabilities Terminal::remoteGetCapabilities(const ::Ice::Current& curr) {
	
}

void Terminal::remoteTryConnect(const ::agh::CallParameters&, const ::Ice::Identity& ident, const ::Ice::Current& curr) {
	stringstream a;
	LOG4CXX_DEBUG(logger, string("Terminal::remoteTryConnect()"));
	masterCallbackPrx = IMasterCallbackPrx::uncheckedCast(curr.con->createProxy(ident));
	
	if (localAddr) {
		delete localAddr;
	}
	if (remoteAddr) {
		delete remoteAddr;
	}
	remoteAddr = new IPV4Address(getRemoteAddressFromConnection(curr.con));
	localAddr = new IPV4Address(getLocalAddressFromConnection(curr.con));
	
	changeState(States::PASSIVE_CONNECTED);
}

void Terminal::remoteStartTransmission(const ::Ice::Current& curr) {
	cout << "XXXX\n";
	cout.flush();
	LOG4CXX_DEBUG(logger, string("Terminal::remoteStartTransmission()"));
	
	if (this->currentState != States::PASSIVE_CONNECTED) {
		LOG4CXX_DEBUG(logger, string("Terminal::remoteStartTransmission() bad state"));
	} else {
		changeState(States::PASSIVE_OPERATIONAL);

		cout << "TRANSCEIVER STARTED\n";
		
		// TODO start RTP.RTCP transmission
		LOG4CXX_DEBUG(logger, string("Terminal::remoteStartTransmission() transmission started"));
	}
}

void Terminal::remoteDisengage(const ::Ice::Current& curr) {
	 
 }

void Terminal::onACK(const ::agh::CallParametersResponse& param) {
	LOG4CXX_DEBUG(logger, string("Terminal::onACK()"));
	
	if (this->currentState != States::ACTIVE_CONNECTED) {
		LOG4CXX_DEBUG(logger, string("Terminal::onACK() bad state"));
	} else {
		remotePort = param.slaveRtpPort;
		
		cout << "XXXX:" << remotePort << endl;
		if (remotePort <= 1024 || remotePort >= 32765 ) {
// 			throw VoipException(); TODO
		}
		
		stringstream a;
		a << "Terminal::onACK() " << "localH: " << *localAddr << " localP:" << localPort \
			<< " remoteH: " << *remoteAddr << " remoteP: "<<  remotePort;
		LOG4CXX_DEBUG(logger, a.str());
		
		// perform connection
		remoteTerminal->remoteStartTransmission();
		LOG4CXX_DEBUG(logger, string("Terminal::onACK() starting transmission"));
// 		this->startTransmission();
		
		cout << "Before change state\n";
		changeState(States::ACTIVE_OPERATIONAL);
		cout << "After change state\n";
	}
}

void Terminal::onNACK() {
	cout << "onNAck received\n";
}

MasterCallbackImpl::MasterCallbackImpl(IMaster *master) : master(master) {
}

void MasterCallbackImpl::remoteTryConnectAck(const ::agh::CallParametersResponse& param, const ::Ice::Current& curr) {
	master->onACK(param);
}

void MasterCallbackImpl::remoteTryConnectNack(const ::Ice::Current& curr) {
	master->onNACK();
}


/*
int Terminal::remoteTryConnect(const Ice::Current& cur) {
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

int Terminal::remoteDisengage(int reason, const Ice::Current& cur) {
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
*/

} /* namespace agh */



