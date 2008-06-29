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
#include <cstdio>


#include <iface.h>
#include "master.h"
#include "restypes.h"
#include "globals.h"
#include "tools.h"
#include "terminal.h"
#include "dummyui.h"
#include "g711.h"



using namespace std;
using namespace agh;
using namespace log4cxx;

int main(int argc, char *argv[]) {

	try {
		// Set up a simple configuration that logs on the console.
		BasicConfigurator::configure();
	} catch(log4cxx::helpers::Exception& e) {
		//clog << e.what() << endl;
	}

	FILE *in = fopen(argv[1], "r+");
	FILE *out = fopen(argv[2], "w+");
	
	G711u codec;
	
	char *inbuf = new char[320];
	char *outbuf = new char[320];
	
	while (!feof(in)) {
		
		fread(inbuf, 160, 1, in);
		codec.decode(outbuf, inbuf, 160);
		fwrite(outbuf, 320, 1, out);
	}
	
	fclose(in);
	fclose(out);
	
/*	int portL = atoi(argv[1]);
	int portR = atoi(argv[2]);
	
	DummyUI *dummy = new DummyUI(portL, portR);
*/
 }
