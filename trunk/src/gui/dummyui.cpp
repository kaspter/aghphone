// #include <iface.h>
// #include "master.h"
// #include "icecommon.h"
// #include <cc++/address.h>
// #include "terminal.h"

#include "dummyui.h"

using namespace std;
using namespace agh;
using namespace ost;
namespace agh {
	
IMasterCallbackPrx masterCallback;

class WorkerThread : public Thread {
	virtual void run();
};

void WorkerThread::run() {
	cout << "sleep in\n";
	cout << "Ringin... Ringing ... phi phi....\n";
	Thread::sleep(5000);
	CallParametersResponse response;
	masterCallback->remoteTryConnectAck(response);
	cout << "sleep out\n";
}

DummyUI::DummyUI(int lIcePort, int rIcePort) {
	terminal = new Terminal(lIcePort, rIcePort);
	terminal->registerCallback(this);
	
	int key;
	while(1) {
		cout << "Key: ";
		cin >> key;
		
		switch(key) {
			case 1 : {
				cout << "IsConencted: " << terminal->isConnected();
				break;
			}
			
			case 2 : {
				cout << "Connecting... " << endl;
				cout << "Remote port: ";
				int remotePort;
				cin >> remotePort;
				int tmpPort;
				cout << "local port: ";
				cin >> tmpPort;
				terminal->setLocalRtpPort(tmpPort);
				terminal->connect("127.0.0.1", remotePort);
				cout << "done\n";
				break;
			}
			
			case 3 : {
				cout << "Starting transmission: "  << endl;
				terminal->startTransmission();
				cout << "started\n";
				break;
			}
			
		}
		cout << endl << endl;
	}
}

bool DummyUI::onStateTransition(int prevState, int curState, const IPV4Address& addr) {
	if (curState == States::PASSIVE_CONNECTED) {

		masterCallback = terminal->getMasterCallback();
		WorkerThread *p = new WorkerThread();
		p->start();
	}
}

} // namespace
