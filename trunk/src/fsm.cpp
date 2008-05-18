/** TODO:
 *  - remove ugly "clog <<" debug method
 *  - add some logging
 *  - ice exception handling
 *  - mutexes
 */

#include <iostream>
#include <map>
#include <Ice/Ice.h>
#include <iface.h>
#include <cc++/address.h>

#include "restypes.h"
#include "globals.h"
#include "tools.h"

using namespace std;
using namespace agh;
using namespace ost;

namespace agh {

const static string adapterName("AGHPhoneAdapter");
const static string componentName("Slave");
const static int defaultIcePort = 24474;
const static int defaultRtpPort = 5004;

/** For TEST ONLY purposes there's possibility to set signalling port
 *  Remove the 'feature' from final version
 */
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

	IPV4Host *remoteHost;

	Ice::CommunicatorPtr ic;
	Ice::ObjectAdapterPtr adapter;

	//Remote object
	ISlavePrx remoteComponent;

public:

	AppComponent(int bindPort);
	~AppComponent();

	/* methods to be remotly invoked for passive connection */
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

	/* methods to be locally invoked for active connection */
	virtual int connect(IPV4Host host, int port);
	virtual void setLocalPort(int port);
	virtual int negotiate();

	/* general methods */
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

int AppComponent::connect(ost::IPV4Host addr, int port = defaultRtpPort) {
	clog << "connect" << endl;
	int res;
	
	if (!addr.isInetAddress()) {
		return ConnectResult::INVALID_HOST;
	}

	if (currentState != DISCONNECTED) {
		return ConnectResult::ALREADY_CONNECTED;
	} else {
		safeDelete(remoteHost);
		remoteHost = new IPV4Host(addr);

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
	int res1 = remoteComponent->setCodec(1);
	int res2 = remoteComponent->setDestinationPort(8888);
	int res3 = remoteComponent->getSourcePort();
}

void AppComponent::setLocalPort(int port) {
	if ((port < 1024) || (port > 32768)) {
		port = defaultRtpPort;
	}

	localPort = defaultRtpPort;
}

} /* namespace agh */

int main(int argc, char *argv[]) {
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
	AppComponent *app = new AppComponent(port);

	if (argc > 1) {
		app->connect("localhost", 8348);
	} else {

	}

	sleep(60);

}

