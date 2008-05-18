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

class ISlaveCallback;
bool operator==(const ISlaveCallback&, const ISlaveCallback&);
bool operator!=(const ISlaveCallback&, const ISlaveCallback&);
bool operator<(const ISlaveCallback&, const ISlaveCallback&);
bool operator<=(const ISlaveCallback&, const ISlaveCallback&);
bool operator>(const ISlaveCallback&, const ISlaveCallback&);
bool operator>=(const ISlaveCallback&, const ISlaveCallback&);

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

class ISlaveCallback;
bool operator==(const ISlaveCallback&, const ISlaveCallback&);
bool operator!=(const ISlaveCallback&, const ISlaveCallback&);
bool operator<(const ISlaveCallback&, const ISlaveCallback&);
bool operator<=(const ISlaveCallback&, const ISlaveCallback&);
bool operator>(const ISlaveCallback&, const ISlaveCallback&);
bool operator>=(const ISlaveCallback&, const ISlaveCallback&);

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

void incRef(::agh::ISlaveCallback*);
void decRef(::agh::ISlaveCallback*);

void incRef(::IceProxy::agh::ISlaveCallback*);
void decRef(::IceProxy::agh::ISlaveCallback*);

void incRef(::agh::ISlave*);
void decRef(::agh::ISlave*);

void incRef(::IceProxy::agh::ISlave*);
void decRef(::IceProxy::agh::ISlave*);

}

namespace agh
{

typedef ::IceInternal::Handle< ::agh::ISlaveCallback> ISlaveCallbackPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::agh::ISlaveCallback> ISlaveCallbackPrx;

void __write(::IceInternal::BasicStream*, const ISlaveCallbackPrx&);
void __read(::IceInternal::BasicStream*, ISlaveCallbackPrx&);
void __write(::IceInternal::BasicStream*, const ISlaveCallbackPtr&);
void __patch__ISlaveCallbackPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const ISlaveCallbackPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const ISlaveCallbackPtr&);
void __decRefUnsafe(const ISlaveCallbackPtr&);
void __clearHandleUnsafe(ISlaveCallbackPtr&);

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

typedef ::std::map< ::Ice::Int, ::Ice::Int> CodecsMap;

class __U__CodecsMap { };
void __write(::IceInternal::BasicStream*, const CodecsMap&, __U__CodecsMap);
void __read(::IceInternal::BasicStream*, CodecsMap&, __U__CodecsMap);

}

namespace IceProxy
{

namespace agh
{

class ISlaveCallback : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int disconnect(::Ice::Int reason)
    {
        return disconnect(reason, 0);
    }
    ::Ice::Int disconnect(::Ice::Int reason, const ::Ice::Context& __ctx)
    {
        return disconnect(reason, &__ctx);
    }
    
private:

    ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);
    
public:
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class ISlave : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int requestConnect()
    {
        return requestConnect(0);
    }
    ::Ice::Int requestConnect(const ::Ice::Context& __ctx)
    {
        return requestConnect(&__ctx);
    }
    
private:

    ::Ice::Int requestConnect(const ::Ice::Context*);
    
public:

    ::agh::CodecsMap getAvailableCodecs()
    {
        return getAvailableCodecs(0);
    }
    ::agh::CodecsMap getAvailableCodecs(const ::Ice::Context& __ctx)
    {
        return getAvailableCodecs(&__ctx);
    }
    
private:

    ::agh::CodecsMap getAvailableCodecs(const ::Ice::Context*);
    
public:

    ::Ice::Int setCodec(::Ice::Int codec)
    {
        return setCodec(codec, 0);
    }
    ::Ice::Int setCodec(::Ice::Int codec, const ::Ice::Context& __ctx)
    {
        return setCodec(codec, &__ctx);
    }
    
private:

    ::Ice::Int setCodec(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int setDestinationPort(::Ice::Int port)
    {
        return setDestinationPort(port, 0);
    }
    ::Ice::Int setDestinationPort(::Ice::Int port, const ::Ice::Context& __ctx)
    {
        return setDestinationPort(port, &__ctx);
    }
    
private:

    ::Ice::Int setDestinationPort(::Ice::Int, const ::Ice::Context*);
    
public:

    ::Ice::Int getSourcePort()
    {
        return getSourcePort(0);
    }
    ::Ice::Int getSourcePort(const ::Ice::Context& __ctx)
    {
        return getSourcePort(&__ctx);
    }
    
private:

    ::Ice::Int getSourcePort(const ::Ice::Context*);
    
public:

    ::Ice::Int startTransmission()
    {
        return startTransmission(0);
    }
    ::Ice::Int startTransmission(const ::Ice::Context& __ctx)
    {
        return startTransmission(&__ctx);
    }
    
private:

    ::Ice::Int startTransmission(const ::Ice::Context*);
    
public:

    ::Ice::Int disconnect(::Ice::Int reason)
    {
        return disconnect(reason, 0);
    }
    ::Ice::Int disconnect(::Ice::Int reason, const ::Ice::Context& __ctx)
    {
        return disconnect(reason, &__ctx);
    }
    
private:

    ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);
    
public:

    void setCallback(const ::agh::ISlaveCallbackPrx& callback)
    {
        setCallback(callback, 0);
    }
    void setCallback(const ::agh::ISlaveCallbackPrx& callback, const ::Ice::Context& __ctx)
    {
        setCallback(callback, &__ctx);
    }
    
private:

    void setCallback(const ::agh::ISlaveCallbackPrx&, const ::Ice::Context*);
    
public:

    ::Ice::Int resetCodec(::Ice::Int codec)
    {
        return resetCodec(codec, 0);
    }
    ::Ice::Int resetCodec(::Ice::Int codec, const ::Ice::Context& __ctx)
    {
        return resetCodec(codec, &__ctx);
    }
    
private:

    ::Ice::Int resetCodec(::Ice::Int, const ::Ice::Context*);
    
public:

    ::agh::ISlaveCallbackPrx getCallback()
    {
        return getCallback(0);
    }
    ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Context& __ctx)
    {
        return getCallback(&__ctx);
    }
    
private:

    ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Context*);
    
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

class ISlaveCallback : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*) = 0;
};

class ISlave : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int requestConnect(const ::Ice::Context*) = 0;

    virtual ::agh::CodecsMap getAvailableCodecs(const ::Ice::Context*) = 0;

    virtual ::Ice::Int setCodec(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int setDestinationPort(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::Ice::Int getSourcePort(const ::Ice::Context*) = 0;

    virtual ::Ice::Int startTransmission(const ::Ice::Context*) = 0;

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*) = 0;

    virtual void setCallback(const ::agh::ISlaveCallbackPrx&, const ::Ice::Context*) = 0;

    virtual ::Ice::Int resetCodec(::Ice::Int, const ::Ice::Context*) = 0;

    virtual ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace agh
{

class ISlaveCallback : virtual public ::IceDelegate::agh::ISlaveCallback,
                       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);
};

class ISlave : virtual public ::IceDelegate::agh::ISlave,
               virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int requestConnect(const ::Ice::Context*);

    virtual ::agh::CodecsMap getAvailableCodecs(const ::Ice::Context*);

    virtual ::Ice::Int setCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int setDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int getSourcePort(const ::Ice::Context*);

    virtual ::Ice::Int startTransmission(const ::Ice::Context*);

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);

    virtual void setCallback(const ::agh::ISlaveCallbackPrx&, const ::Ice::Context*);

    virtual ::Ice::Int resetCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace agh
{

class ISlaveCallback : virtual public ::IceDelegate::agh::ISlaveCallback,
                       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);
};

class ISlave : virtual public ::IceDelegate::agh::ISlave,
               virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int requestConnect(const ::Ice::Context*);

    virtual ::agh::CodecsMap getAvailableCodecs(const ::Ice::Context*);

    virtual ::Ice::Int setCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int setDestinationPort(::Ice::Int, const ::Ice::Context*);

    virtual ::Ice::Int getSourcePort(const ::Ice::Context*);

    virtual ::Ice::Int startTransmission(const ::Ice::Context*);

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Context*);

    virtual void setCallback(const ::agh::ISlaveCallbackPrx&, const ::Ice::Context*);

    virtual ::Ice::Int resetCodec(::Ice::Int, const ::Ice::Context*);

    virtual ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Context*);
};

}

}

namespace agh
{

class ISlaveCallback : virtual public ::Ice::Object
{
public:

    typedef ISlaveCallbackPrx ProxyType;
    typedef ISlaveCallbackPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___disconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ISlaveCallbackPtr(void*, ::Ice::ObjectPtr&);

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

    virtual ::Ice::Int requestConnect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___requestConnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::CodecsMap getAvailableCodecs(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getAvailableCodecs(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int setCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int setDestinationPort(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setDestinationPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int getSourcePort(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getSourcePort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int startTransmission(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___startTransmission(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int disconnect(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___disconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void setCallback(const ::agh::ISlaveCallbackPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___setCallback(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int resetCodec(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___resetCodec(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::ISlaveCallbackPrx getCallback(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getCallback(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ISlavePtr(void*, ::Ice::ObjectPtr&);

}

#endif
