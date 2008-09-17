// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.2.1
// Generated from file `directory.ice'

#ifndef __directory_h__
#define __directory_h__

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
#include <Ice/UserExceptionFactory.h>
#include <Ice/FactoryTable.h>
#include <Ice/StreamF.h>
#include <../ice/icecommon.h>
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

class Directory;
bool operator==(const Directory&, const Directory&);
bool operator!=(const Directory&, const Directory&);
bool operator<(const Directory&, const Directory&);
bool operator<=(const Directory&, const Directory&);
bool operator>(const Directory&, const Directory&);
bool operator>=(const Directory&, const Directory&);

}

}

namespace agh
{

class Directory;
bool operator==(const Directory&, const Directory&);
bool operator!=(const Directory&, const Directory&);
bool operator<(const Directory&, const Directory&);
bool operator<=(const Directory&, const Directory&);
bool operator>(const Directory&, const Directory&);
bool operator>=(const Directory&, const Directory&);

}

namespace IceInternal
{

void incRef(::agh::Directory*);
void decRef(::agh::Directory*);

void incRef(::IceProxy::agh::Directory*);
void decRef(::IceProxy::agh::Directory*);

}

namespace agh
{

typedef ::IceInternal::Handle< ::agh::Directory> DirectoryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::agh::Directory> DirectoryPrx;

void __write(::IceInternal::BasicStream*, const DirectoryPrx&);
void __read(::IceInternal::BasicStream*, DirectoryPrx&);
void __write(::IceInternal::BasicStream*, const DirectoryPtr&);
void __patch__DirectoryPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const DirectoryPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const DirectoryPtr&);
void __decRefUnsafe(const DirectoryPtr&);
void __clearHandleUnsafe(DirectoryPtr&);

}

namespace agh
{

class DirectoryException : public ::agh::VoipException
{
public:

    DirectoryException() {}
    virtual ~DirectoryException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

static DirectoryException __DirectoryException_init;

class BadLoginException : public ::agh::DirectoryException
{
public:

    BadLoginException() {}
    virtual ~BadLoginException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class NoSuchTerminalException : public ::agh::DirectoryException
{
public:

    NoSuchTerminalException() {}
    virtual ~NoSuchTerminalException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

class TerminalExistsException : public ::agh::DirectoryException
{
public:

    TerminalExistsException() {}
    virtual ~TerminalExistsException() throw();

    virtual ::std::string ice_name() const;
    virtual ::Ice::Exception* ice_clone() const;
    virtual void ice_throw() const;

    static const ::IceInternal::UserExceptionFactoryPtr& ice_factory();

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);

    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

typedef ::std::vector< ::agh::TerminalAddress> Terminals;

class __U__Terminals { };
void __write(::IceInternal::BasicStream*, const ::agh::TerminalAddress*, const ::agh::TerminalAddress*, __U__Terminals);
void __read(::IceInternal::BasicStream*, Terminals&, __U__Terminals);

}

namespace IceProxy
{

namespace agh
{

class Directory : virtual public ::IceProxy::Ice::Object
{
public:

    void registerTerminal(const ::agh::TerminalAddress& address)
    {
        registerTerminal(address, 0);
    }
    void registerTerminal(const ::agh::TerminalAddress& address, const ::Ice::Context& __ctx)
    {
        registerTerminal(address, &__ctx);
    }
    
private:

    void registerTerminal(const ::agh::TerminalAddress&, const ::Ice::Context*);
    
public:

    void removeTerminal(const ::std::string& name)
    {
        removeTerminal(name, 0);
    }
    void removeTerminal(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        removeTerminal(name, &__ctx);
    }
    
private:

    void removeTerminal(const ::std::string&, const ::Ice::Context*);
    
public:

    ::agh::TerminalAddress findTerminal(const ::std::string& name)
    {
        return findTerminal(name, 0);
    }
    ::agh::TerminalAddress findTerminal(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return findTerminal(name, &__ctx);
    }
    
private:

    ::agh::TerminalAddress findTerminal(const ::std::string&, const ::Ice::Context*);
    
public:

    ::agh::Terminals findTerminals(const ::std::string& name)
    {
        return findTerminals(name, 0);
    }
    ::agh::Terminals findTerminals(const ::std::string& name, const ::Ice::Context& __ctx)
    {
        return findTerminals(name, &__ctx);
    }
    
private:

    ::agh::Terminals findTerminals(const ::std::string&, const ::Ice::Context*);
    
public:

    ::agh::Terminals getTerminals()
    {
        return getTerminals(0);
    }
    ::agh::Terminals getTerminals(const ::Ice::Context& __ctx)
    {
        return getTerminals(&__ctx);
    }
    
private:

    ::agh::Terminals getTerminals(const ::Ice::Context*);
    
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

class Directory : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void registerTerminal(const ::agh::TerminalAddress&, const ::Ice::Context*) = 0;

    virtual void removeTerminal(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::agh::TerminalAddress findTerminal(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::agh::Terminals findTerminals(const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::agh::Terminals getTerminals(const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace agh
{

class Directory : virtual public ::IceDelegate::agh::Directory,
                  virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void registerTerminal(const ::agh::TerminalAddress&, const ::Ice::Context*);

    virtual void removeTerminal(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::TerminalAddress findTerminal(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::Terminals findTerminals(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::Terminals getTerminals(const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace agh
{

class Directory : virtual public ::IceDelegate::agh::Directory,
                  virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void registerTerminal(const ::agh::TerminalAddress&, const ::Ice::Context*);

    virtual void removeTerminal(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::TerminalAddress findTerminal(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::Terminals findTerminals(const ::std::string&, const ::Ice::Context*);

    virtual ::agh::Terminals getTerminals(const ::Ice::Context*);
};

}

}

namespace agh
{

class Directory : virtual public ::Ice::Object
{
public:

    typedef DirectoryPrx ProxyType;
    typedef DirectoryPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void registerTerminal(const ::agh::TerminalAddress&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___registerTerminal(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void removeTerminal(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___removeTerminal(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::TerminalAddress findTerminal(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___findTerminal(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::Terminals findTerminals(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___findTerminals(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::agh::Terminals getTerminals(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getTerminals(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__DirectoryPtr(void*, ::Ice::ObjectPtr&);

}

#endif
