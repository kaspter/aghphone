#ifndef __TRANSCIEVER_H__INCLUDED__
#define __TRANSCIEVER_H__INCLUDED__

#include <vector>
#include <cc++/address.h>

using namespace std;
using namespace ost;

namespace agh {

class IDevice {
	
};

class ITransciever {
	vector<IDevice> getAvailableInputDevices();
	vector<IDevice> getAvailableOutputDevices();
	int setInputDevice(const IDevice& dev);
	int setOutputDevice(const IDevice& dev);
	int setCodec(int codec);
	int setLocalEndpoint(const IPV4Address& addr, int port);
	int setRemoteEndpoint(const IPV4Address& addr, int port);
	
	int start();
	int stop();
};

} /* namespace agh */

#endif /* __TRANSCIEVER_H__INCLUDED__ */
