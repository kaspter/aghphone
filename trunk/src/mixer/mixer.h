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

#ifndef __MIXER_H__INCLUDED__
#define __MIXER_H__INCLUDED__

#include <Ice/Ice.h>
#include <Ice/Identity.h>

#include <string>
#include <vector>

#include "tools.h"
// #include "icecommon.h"
#include "iface.h"
#include "states.h"
// #include "../ice/states.h"

// #include "../common/master.h"
// #include "../ice/icecommon.h"


// #include "../ice/iface.h"
// #include "../common/restypes.h"
// #include "../common/globals.h"
// #include "../common/tools.h"
// #include "../ice/icecommon.h"
// #include "../transceiver/transceiver.h"

// #include "../common/states.h"

using namespace std;
using namespace ost;

namespace agh {

class Mixer : public ISlave {
protected:
	const static string adapterName;
	const static string adapterCallbackName;
	const static string remoteMixerName;
	const static int defaultIcePort;
	const static int defaultRtpPort;

	int codec;

	int remotePort;
	int localPort;

	int remoteIcePort;
	int localIcePort;

	IPV4Address *localAddr;
	IPV4Address *remoteAddr;

	int currentState;

	Ice::CommunicatorPtr ic;
	Ice::ObjectAdapterPtr adapter;
	
// 	ISlavePrx remoteMixer;
	IMasterCallbackPtr masterCallbackPtr;
	IMasterCallbackPrx masterCallbackPrx;
	
	vector<IPV4Address> remoteHosts;

public:
	Mixer(int lIcePort = defaultIcePort);
	virtual ~Mixer();
	
	virtual bool isConnected() const; // TODO getState
	virtual void setLocalRtpPort(int port);
	virtual int getLocalRtpPort() const;
	virtual int getDestinationRtpPort() const;
	virtual const IPV4Address *getRemoteHost() const;
	virtual const IPV4Address *getLocalHost() const;
    
	/* ISlave */
    virtual TerminalCapabilities remoteGetCapabilities(const ::Ice::Current& curr);
    virtual void remoteTryConnect(const ::agh::CallParameters&, const ::Ice::Identity& ident, const ::Ice::Current& curr);
    virtual void remoteStartTransmission(const ::Ice::Current& curr);
    virtual void remoteDisengage(const ::Ice::Current& curr); 
	
	/* IMixer */
	virtual void foo(const ::Ice::Current& curr);
private:
	void changeState(int newState);
};

} /* namespace */

#endif /* __TERMINAL_H__INCLUDED__ */
