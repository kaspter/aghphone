#include "tools.h"
#include <cc++/socket.h>
#include <Ice/Ice.h>
#include <cstdio>
#include <strstream>
#include <boost/regex.hpp>

using namespace agh;
using namespace ost;
using namespace std;
using namespace boost;

namespace agh {

IPV4Host getHostFromConnection(Ice::ConnectionPtr con) {
	
	regex expr("^remote address = ([.0-9]+):[0-9]+");
	
	string text = con->toString();
	stringstream stream(text);
	string line;
	
	cmatch what;
	
	while(getline(stream, line)) {
		if (regex_match(line.c_str(), what, expr)) {
			cout << what[1] << endl;
		}
	}
	return IPV4Host(String(what[1]));
}

} /* namespace agh */