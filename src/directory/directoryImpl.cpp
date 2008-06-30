#include <Ice/Ice.h>
#include <map>
#include "../ice/icecommon.h"
#include "directory.h"

using namespace std;
using namespace agh;

class DirectoryImpl : public Directory
{
	private:
		map<string, TerminalAddress> terminals;
	public:
		virtual void registerTerminal(const TerminalAddress& address, const Ice::Current&);
		virtual void removeTerminal(const string& address, const Ice::Current&);
		virtual TerminalAddress findTerminal(const string& address, const Ice::Current&);
		virtual Terminals getTerminals(const Ice::Current&);
};

Terminals DirectoryImpl::getTerminals(const Ice::Current&) {
	map<string, TerminalAddress>::iterator iter;
	Terminals retTerminals;
	
	for( iter = terminals.begin(); iter != terminals.end(); iter++ ) {
		retTerminals.push_back(iter->first);
	}
	
	return retTerminals;
}

void DirectoryImpl::registerTerminal(const TerminalAddress& address, const Ice::Current&) {
	if (address.name == "") {
		throw BadLoginException();
	}
	if (terminals.count(address.name) > 0) {
		throw TerminalExistsException();
	}
	
	terminals[address.name] = address;
	
	cout << address.name << " successfully registered" << endl;
}

void DirectoryImpl::removeTerminal(const string& address, const Ice::Current&) {
	
	if (terminals.count(address) <= 0) {
		throw NoSuchTerminalException();
	}
	
	terminals.erase(address);
	
	cout << address << " successfully unregistered" << endl;
}

TerminalAddress DirectoryImpl::findTerminal(const string& address, const Ice::Current&) {
	
	if (terminals.count(address) <= 0) {
		throw NoSuchTerminalException();
	}
	
	TerminalAddress retAddress = terminals[address];
	
	return retAddress;
}

int main ( int argc, char* argv[] )
{
	if (argc < 3) {
		cout << "bad parameters\n";
		cout << "usage: directory name port\n";
		return 1;
	}
	
	string name = argv[1];
	string port = argv[2];
	
	int status = 0;
	Ice::CommunicatorPtr ic;
	try
	{
		ic = Ice::initialize ( );
		stringstream iceEndpoint;
		iceEndpoint << "default -p " << port;	
		
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints(name,
				iceEndpoint.str());
		
		Ice::ObjectPtr object = new DirectoryImpl;
		adapter->add( object, ic->stringToIdentity(name));
		adapter->activate();
	
		ic->waitForShutdown();
	
	}
	catch ( const Ice::Exception& e )
	{
		cerr << e << endl;
		status = 1;
	}
	catch ( const char* msg )
	{
		cerr << msg << endl;
		status = 1;
	}
	if ( ic )
	{
		try
		{
			ic->destroy();
		}
		catch ( const Ice::Exception& e )
		{
			cerr << e << endl;
			status = 1;
		}
	}
	
	return status;
}
