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
	this->lIcePort = lIcePort;
	this->rIcePort = rIcePort;
	terminal = new Terminal(lIcePort, rIcePort);
	terminal->registerCallback(this);
	
	int key;
	while(1) {

		cout << "\n================================================\n";
		cout << "1. IsConencted\n";
		cout << "2. Connect directly usind IP address... \n";
		cout << "3. Start transmission established using 2.\n";
		cout << "4. Locate directory\n";
		cout << "5. Register in the directory\n";
		cout << "6. Connect and start transmission via user alias using directory\n";
		cout << "================================================\n";
		
		cout << "Your choice: ";
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
			
			case 4 : {
				cout << "Locate directory: "  << endl;
				string directoryAddress;
				string directoryPort;
				cout << "directory host name: ";
				cin >> directoryAddress;
				cout << "direcotry port: ";
				cin >> directoryPort;
				this->findDirectory(directoryPort, directoryAddress);
				break;
			}
			
			case 5 : {
				cout << "Register in directory: "  << endl;
				
				TerminalAddress address;
				std::ostringstream o;
				o << string("127.0.0.1") << this->lIcePort;
				address.name = o.str();
				std::ostringstream o2;
				o2 << string("") << this->lIcePort;
				address.port = o2.str();
				address.ipAddress = string("127.0.0.1");
				
				try {
					this->directory->registerTerminal(address);
				} catch(BadLoginException e) {
					cerr << "Bad login\n";
				} catch(TerminalExistsException e) {
					cerr << "Terminal already exists\n";
				}
				
				cout << "started\n";
				break;
			}
			
			case 6 : {
				cout << "Find in directory & establish connection: "  << endl;
				
				string slaveName;
				cout << "Slave name: ";
				cin >> slaveName;
				TerminalAddress addr;
				
				try {
					addr = this->directory->findTerminal(slaveName);
				} catch(VoipException) {
					cerr << "address retrieve error\n";
					return;
				}
				
				cout << "terminal found!" << endl;
				cout << "name: " << addr.name << endl;
				cout << "address: " << addr.ipAddress << endl;
				cout << "port: " << addr.port << endl;
				
				istringstream myStream(addr.port);
				int tmpPort;
				myStream >> tmpPort;
				
				terminal->setLocalRtpPort(this->lIcePort);
				terminal->connect(addr.ipAddress.c_str(), tmpPort);
				
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

void DummyUI::findDirectory(string port, string name) {
	char **argv;
	Ice::CommunicatorPtr ic = Ice::initialize ();
	Ice::ObjectPrx base = ic->stringToProxy ( string("Directory")+":default -p "+port );
	directory = DirectoryPrx::checkedCast ( base );
	if ( !directory )
		throw "Invalid proxy";
}

} // namespace
