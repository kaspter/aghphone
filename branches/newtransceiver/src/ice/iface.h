// **********************************************************************
//
// Copyright (c) 2003-2008 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.0
// Generated from file `iface.ice'

#ifndef __iface_h__
#define __iface_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 303
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace agh
{

class ISlave;

}

}

namespace agh
{

class ISlave;
bool operator==(const ISlave&, const ISlave&);
bool operator<(const ISlave&, const ISlave&);

}

namespace IceInternal
{

::Ice::Object* upCast(::agh::ISlave*);
::IceProxy::Ice::Object* upCast(::IceProxy::agh::ISlave*);

}

namespace agh
{

typedef ::IceInternal::Handle< ::agh::ISlave> ISlavePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::agh::ISlave> ISlavePrx;

void __read(::IceInternal::BasicStream*, ISlavePrx&);
void __patch__ISlavePtr(void*, ::Ice::ObjectPtr&);

}

namespace agh
{

typedef ::std::vector< ::Ice::Int> prefferedCodecs;

}

namespace IceProxy
{

namespace agh
{

class ISlave : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int remoteConnect()
    {
        return remoteConnect(0);
    }
    ::Ice::Int remoteConnect(const ::Ice::Context& __ctx)
    {
        return remoteConnect(&__ctx);
    }
    
private:

    ::Ice::Int remoteConnect(const ::Ice::Context*);
    
public:

    ::Ice::Int remoteDisconnect(::Ice::Int reason)
    {
        return remoteDisconnect(reason, 0);
    }
    ::Ice::Int remoteDisconnect(::Ice::Int reason, const ::Ice::Context& __ctx)
    {
        return remoteDisconnect(reason, &__ctx);
    }
    
private:

    ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int remotePing()
    {
        return remotePing(0);
    }
    ::Ice::Int remotePing(const ::Ice::Context& __ctx)
    {
        return remotePing(&__ctx);
    }
    
private:

    ::Ice::Int remotePing(const ::Ice::Context*);
    
public:

    ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec()
    {
        return remoteGetPrefferedOutgoingCodec(0);
    }
    ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Context& __ctx)
    {
        return remoteGetPrefferedOutgoingCodec(&__ctx);
    }
    
private:

    ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Context*);
    
public:

    ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec()
    {
        return remoteGetPrefferedIncomingCodec(0);
    }
    ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Context& __ctx)
    {
        return remoteGetPrefferedIncomingCodec(&__ctx);
    }
    
private:

    ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Context*);
    
public:

    ::Ice::Int remoteSetOutgoingCodec(::Ice::Int codec)
    {
        return remoteSetOutgoingCodec(codec, 0);
    }
    ::Ice::Int remoteSetOutgoingCodec(::Ice::Int codec, const ::Ice::Context& __ctx)
    {
        return remoteSetOutgoingCodec(codec, &__ctx);
    }
    
private:

    ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int remoteResetOutgoingCodec(::Ice::Int codec)
    {
        return remoteResetOutgoingCodec(codec, 0);
    }
    ::Ice::Int remoteResetOutgoingCodec(::Ice::Int codec, const ::Ice::Context& __ctx)
    {
        return remoteResetOutgoingCodec(codec, &__ctx);
    }
    
private:

    ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int remoteSetDestinationPort(::Ice::Int port)
    {
        return remoteSetDestinationPort(port, 0);
    }
    ::Ice::Int remoteSetDestinationPort(::Ice::Int port, const ::Ice::Context& __ctx)
    {
        return remoteSetDestinationPort(port, &__ctx);
    }
    
private:

    ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int remoteGetDestinationPort(::Ice::Int port)
    {
        return remoteGetDestinationPort(port, 0);
    }
    ::Ice::Int remoteGetDestinationPort(::Ice::Int port, const ::Ice::Context& __ctx)
    {
        return remoteGetDestinationPort(port, &__ctx);
    }
    
private:

    ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int remoteGetSourcePort()
    {
        return remoteGetSourcePort(0);
    }
    ::Ice::Int remoteGetSourcePort(const ::Ice::Context& __ctx)
    {
        return remoteGetSourcePort(&__ctx);
    }
    
private:

    ::Ice::Int remoteGetSourcePort(const ::Ice::Context*);
    
public:

    ::Ice::Int remoteStartTransmission()
    {
        return remoteStartTransmission(0);
    }
    ::Ice::Int remoteStartTransmission(const ::Ice::Context& __ctx)
    {
        return remoteStartTransmission(&__ctx);
    }
    
private:

    ::Ice::Int remoteStartTransmission(const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<ISlave> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<ISlave> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<ISlave*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<ISlave*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace agh
{

class ISlave : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int remoteConnect(const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int remotePing(const ::Ice::Context*) = 0;

    virtual ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Context*) = 0;

    virtual ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteGetSourcePort(const ::Ice::Context*) = 0;

    virtual ::Ice::Int remoteStartTransmission(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace agh
{

class ISlave : virtual public ::IceDelegate::agh::ISlave,
               virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int remoteConnect(const ::Ice::Context*);

    virtual ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remotePing(const ::Ice::Context*);

    virtual ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Context*);

    virtual ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Context*);

    virtual ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteGetSourcePort(const ::Ice::Context*);

    virtual ::Ice::Int remoteStartTransmission(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace agh
{

class ISlave : virtual public ::IceDelegate::agh::ISlave,
               virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int remoteConnect(const ::Ice::Context*);

    virtual ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remotePing(const ::Ice::Context*);

    virtual ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Context*);

    virtual ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Context*);

    virtual ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int remoteGetSourcePort(const ::Ice::Context*);

    virtual ::Ice::Int remoteStartTransmission(const ::Ice::Context*);
};

}

}

namespace agh
{

class ISlave : virtual public ::Ice::Object
{
public:

    typedef ISlavePrx ProxyType;
    typedef ISlavePtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int remoteConnect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteConnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteDisconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remotePing(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remotePing(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteGetPrefferedOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteGetPrefferedIncomingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteSetOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteResetOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteSetDestinationPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteGetDestinationPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteGetSourcePort(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteGetSourcePort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteStartTransmission(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___remoteStartTransmission(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif
