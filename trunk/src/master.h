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

#ifndef __MASTER_H__INCLUDED__
#define __MASTER_H__INCLUDED__

#include "transceiver.h"

#include <cc++/address.h>

using namespace ost;

namespace agh {

class ICallback {
	
public:
	virtual ~ICallback() = 0;
	
	virtual bool onIncomingCall(const IPV4Address& addr) = 0;
	
	virtual bool onDisconnect() = 0;
	virtual bool onConnect() = 0;
};

class IMaster {
	
public:
	
	virtual bool isConnected() const = 0;
	
	virtual int setLocalPort(int port) = 0;
	virtual int getLocalPort() const = 0;
	virtual int getDestinationPort() const = 0;
	virtual const IPV4Address *getRemoteHost() const = 0;
	virtual const IPV4Address *getLocalHost() const = 0;
	
	virtual int connect(const IPV4Address& addr, int icePort) = 0;
	virtual int disconnect() = 0;
	
	virtual int startTransmission() = 0;
	
	virtual int registerCallback(ICallback *callback) = 0;
	virtual int unregisterCallback(int id) = 0;
	
	virtual int setTransceiver(ITransceiver *transceiver) = 0;
	virtual int unsetTransceiver() = 0;
};

} /* namespace agh */

#endif /* __MASTER_H__INCLUDED__ */
