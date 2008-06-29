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

#include "mixer.h"

using namespace std;
using namespace agh;
using namespace ost;

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace agh {

static LoggerPtr logger(Logger::getLogger("MixerCPP"));

const string Mixer::adapterName("AGHPhoneAdapter");
const string Mixer::adapterCallbackName("AGHPhoneCallbackAdapter");
const string Mixer::remoteMixerName("Slave");
const int Mixer::defaultIcePort = 24474;
const int Mixer::defaultRtpPort = 5004;

Mixer::Mixer(int lIcePort) :
			localRTPPort(defaultRtpPort),
			localIcePort(lIcePort), localAddr(0),
			remoteAddr(0), currentState(States::DISCONNECTED), ic(0), adapter(0) {
	
	cout << "Constructor of mixer" << endl;
	
	if ((localIcePort < 1024) || (localIcePort > 32768))
		localIcePort = defaultIcePort;

	ic = Ice::initialize();
	stringstream iceEndpoint;
	iceEndpoint << "default -p " << localIcePort;
	adapter = ic->createObjectAdapterWithEndpoints(adapterName,
			iceEndpoint.str());
	ISlavePtr localMixer = this;
	adapter->add(localMixer, ic->stringToIdentity(remoteMixerName));
	adapter->activate();
	
	LOG4CXX_DEBUG(logger, "Mixer::Mixer adapter activated()");
	ic->waitForShutdown(); // TODO to remove
}

Mixer::~Mixer() {
	
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

bool Mixer::isConnected() const {
	return currentState != States::DISCONNECTED;
}

void Mixer::setLocalRtpPort(int port) {
	if ((port < 1024) || (port > 32768)) {
	} else {
		localRTPPort = port;
	}
}

int Mixer::getLocalRtpPort() const {
	return localRTPPort;
}

const IPV4Address* Mixer::getRemoteHost() const {
	return remoteAddr;
}

const IPV4Address* Mixer::getLocalHost() const {
	return localAddr;
}

void Mixer::changeState(int newState) {
	stringstream a;
	LOG4CXX_DEBUG(logger, "Mixer::changeState()");
	
	a << string("Mixer::changeState() prev: ") << this->currentState << " new: " << newState;
	LOG4CXX_DEBUG(logger, a.str());
	this->currentState = newState;
}

TerminalCapabilities Mixer::remoteGetCapabilities(const ::Ice::Current& curr) {
	// TODO	
}

void Mixer::remoteTryConnect(const ::agh::CallParameters& params, const ::Ice::Identity& ident, const ::Ice::Current& curr) {
	stringstream a;
	LOG4CXX_DEBUG(logger, string("Mixer::remoteTryConnect()"));
	masterCallbackPrx = IMasterCallbackPrx::uncheckedCast(curr.con->createProxy(ident));
	
	if (localAddr) {
		delete localAddr;
	}
	if (remoteAddr) {
		delete remoteAddr;
	}
	
	// TODO input/output codecs 
	IPV4Address *tmpAddr = new IPV4Address(getRemoteAddressFromConnection(curr.con));
	TerminalInfo info;
	info.address = *tmpAddr;
	info.rtpPort = params.masterRtpPort;
	remoteHosts.push_back(info);
	a << "Mixer::remoteTryConnect() conf received, remote addr: " << tmpAddr << " port: " << params.masterRtpPort;
 	LOG4CXX_DEBUG(logger, a.str());
	
	changeState(States::PASSIVE_CONNECTED);
	
	// inform remote site
	CallParametersResponse response;
	response.slaveRtpPort = localRTPPort;
	masterCallbackPrx->remoteTryConnectAck(response);
}

void Mixer::remoteStartTransmission(const ::Ice::Current& curr) {
	LOG4CXX_DEBUG(logger, string("Mixer::remoteStartTransmission()"));
	
	if (this->currentState != States::PASSIVE_CONNECTED) {
		LOG4CXX_DEBUG(logger, string("Mixer::remoteStartTransmission() bad state"));
	} else {
		changeState(States::PASSIVE_OPERATIONAL);

		cout << "TRANSCEIVER STARTED\n";
		
		// TODO start RTP.RTCP transmission
		LOG4CXX_DEBUG(logger, string("Mixer::remoteStartTransmission() transmission started"));
	}
}

void Mixer::remoteDisengage(const ::Ice::Current& curr) {
	// TODO	 
}

void Mixer::foo(const ::Ice::Current& curr) {
	
}

} /* namespace agh */

int main() {
	
	try {
		// Set up a simple configuration that logs on the console.
		BasicConfigurator::configure();
	} catch(log4cxx::helpers::Exception& e) {
		//clog << e.what() << endl;
	}
	
	Mixer m(12345);
	m.setLocalRtpPort(22222);
	
	std::cout << "mixer is running...\n";
}



