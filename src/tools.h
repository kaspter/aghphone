#ifndef __TOOLS_H__INCLUDED__
#define __TOOLS_H__INCLUDED__

#include <Ice/Ice.h>
#include <cc++/socket.h>
#include <iface.h>

#define safeDelete(ptr) {	\
	if ((ptr)) delete ptr;	\
	(ptr) = 0;				\
}

namespace agh {

extern ost::IPV4Host getHostFromConnection(Ice::ConnectionPtr con);
extern int chooseBestCodec(CodecsMap codecsMap);

} /* namespace agh */

#endif /* __TOOLS_H__INCLUDED__ */
