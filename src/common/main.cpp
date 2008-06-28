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
#include "terminal.h"

using namespace std;
using namespace agh;
using namespace log4cxx;

int main(int argc, char *argv[]) {

	try {
		// Set up a simple configuration that logs on the console.
		BasicConfigurator::configure();
	} catch(log4cxx::helpers::Exception& e) {
		clog << e.what() << endl;
	}

	Terminal *term;

	if (argc > 1) {
		term = new Terminal(3000, 4000);
	} else {
		term = new Terminal(4000, 3000);
		term->connect("127.0.0.1", 3000);
	}
	int g;
	cin >> g;
}

/*
 int main(int argc, char *argv[]) {


 TransceiverAlsa *itr = new TransceiverAlsa();
 itr->setLocalEndpoint(argv[1], atoi(argv[2]));
 itr->setRemoteEndpoint(argv[3], atoi(argv[4]));
 
 if(argc >= 6)
 itr->setInputDevice(argv[5]);
 if(argc >= 7)
 itr->setOutputDevice(argv[6]);
 
 itr->start();
 
 cout << "Press any key to exit..." << endl;
 cin.get();
 
 delete itr;
 }
 */