// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
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
#   if ICE_INT_VERSION / 100 != 302
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace agh
{

class ISlave;
bool operator==(const ISlave&, const ISlave&);
bool operator!=(const ISlave&, const ISlave&);
bool operator<(const ISlave&, const ISlave&);
bool operator<=(const ISlave&, const ISlave&);
bool operator>(const ISlave&, const ISlave&);
bool operator>=(const ISlave&, const ISlave&);

}

}

namespace agh
{

class ISlave;
bool operator==(const ISlave&, const ISlave&);
bool operator!=(const ISlave&, const ISlave&);
bool operator<(const ISlave&, const ISlave&);
bool operator<=(const ISlave&, const ISlave&);
bool operator>(const ISlave&, const ISlave&);
bool operator>=(const ISlave&, const ISlave&);

}

namespace IceInternal
{

void incRef(::agh::ISlave*);
void decRef(::agh::ISlave*);

void incRef(::IceProxy::agh::ISlave*);
void decRef(::IceProxy::agh::ISlave*);

}

namespace agh
{

typedef ::IceInternal::Handle< ::agh::ISlave> ISlavePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::agh::ISlave> ISlavePrx;

void __write(::IceInternal::BasicStream*, const ISlavePrx&);
void __read(::IceInternal::BasicStream*, ISlavePrx&);
void __write(::IceInternal::BasicStream*, const ISlavePtr&);
void __patch__ISlavePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const ISlavePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const ISlavePtr&);
void __decRefUnsafe(const ISlavePtr&);
void __clearHandleUnsafe(ISlavePtr&);

}

namespace agh
{

typedef ::std::vector< ::Ice::Int> prefferedCodecs;

class __U__prefferedCodecs { };

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
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
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
    ::IceInternal::DispatchStatus ___remoteConnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteDisconnect(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteDisconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remotePing(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remotePing(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::prefferedCodecs remoteGetPrefferedOutgoingCodec(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteGetPrefferedOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::prefferedCodecs remoteGetPrefferedIncomingCodec(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteGetPrefferedIncomingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteSetOutgoingCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteSetOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteResetOutgoingCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteResetOutgoingCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteSetDestinationPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteSetDestinationPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteGetDestinationPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteGetDestinationPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteGetSourcePort(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteGetSourcePort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int remoteStartTransmission(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___remoteStartTransmission(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ISlavePtr(void*, ::Ice::ObjectPtr&);

}

#endif
