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

#include <directory.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/ScopedArray.h>

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

static const ::std::string __agh__Directory__registerTerminal_name = "registerTerminal";

static const ::std::string __agh__Directory__removeTerminal_name = "removeTerminal";

static const ::std::string __agh__Directory__findTerminal_name = "findTerminal";

static const ::std::string __agh__Directory__findTerminals_name = "findTerminals";

static const ::std::string __agh__Directory__getTerminals_name = "getTerminals";

void
IceInternal::incRef(::agh::Directory* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::agh::Directory* p)
{
    p->__decRef();
}

void
IceInternal::incRef(::IceProxy::agh::Directory* p)
{
    p->__incRef();
}

void
IceInternal::decRef(::IceProxy::agh::Directory* p)
{
    p->__decRef();
}

void
agh::__write(::IceInternal::BasicStream* __os, const ::agh::DirectoryPrx& v)
{
    __os->write(::Ice::ObjectPrx(v));
}

void
agh::__read(::IceInternal::BasicStream* __is, ::agh::DirectoryPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::agh::Directory;
        v->__copyFrom(proxy);
    }
}

void
agh::__write(::IceInternal::BasicStream* __os, const ::agh::DirectoryPtr& v)
{
    __os->write(::Ice::ObjectPtr(v));
}

agh::DirectoryException::~DirectoryException() throw()
{
}

static const char* __agh__DirectoryException_name = "agh::DirectoryException";

::std::string
agh::DirectoryException::ice_name() const
{
    return __agh__DirectoryException_name;
}

::Ice::Exception*
agh::DirectoryException::ice_clone() const
{
    return new DirectoryException(*this);
}

void
agh::DirectoryException::ice_throw() const
{
    throw *this;
}

void
agh::DirectoryException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::agh::DirectoryException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    VoipException::__write(__os);
#else
    ::agh::VoipException::__write(__os);
#endif
}

void
agh::DirectoryException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    VoipException::__read(__is, true);
#else
    ::agh::VoipException::__read(__is, true);
#endif
}

void
agh::DirectoryException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::DirectoryException was not generated with stream support";
    throw ex;
}

void
agh::DirectoryException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::DirectoryException was not generated with stream support";
    throw ex;
}

struct __F__agh__DirectoryException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::agh::DirectoryException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__agh__DirectoryException__Ptr = new __F__agh__DirectoryException;

const ::IceInternal::UserExceptionFactoryPtr&
agh::DirectoryException::ice_factory()
{
    return __F__agh__DirectoryException__Ptr;
}

class __F__agh__DirectoryException__Init
{
public:

    __F__agh__DirectoryException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::agh::DirectoryException", ::agh::DirectoryException::ice_factory());
    }

    ~__F__agh__DirectoryException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::agh::DirectoryException");
    }
};

static __F__agh__DirectoryException__Init __F__agh__DirectoryException__i;

#ifdef __APPLE__
extern "C" { void __F__agh__DirectoryException__initializer() {} }
#endif

agh::BadLoginException::~BadLoginException() throw()
{
}

static const char* __agh__BadLoginException_name = "agh::BadLoginException";

::std::string
agh::BadLoginException::ice_name() const
{
    return __agh__BadLoginException_name;
}

::Ice::Exception*
agh::BadLoginException::ice_clone() const
{
    return new BadLoginException(*this);
}

void
agh::BadLoginException::ice_throw() const
{
    throw *this;
}

void
agh::BadLoginException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::agh::BadLoginException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__write(__os);
#else
    ::agh::DirectoryException::__write(__os);
#endif
}

void
agh::BadLoginException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__read(__is, true);
#else
    ::agh::DirectoryException::__read(__is, true);
#endif
}

void
agh::BadLoginException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::BadLoginException was not generated with stream support";
    throw ex;
}

void
agh::BadLoginException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::BadLoginException was not generated with stream support";
    throw ex;
}

struct __F__agh__BadLoginException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::agh::BadLoginException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__agh__BadLoginException__Ptr = new __F__agh__BadLoginException;

const ::IceInternal::UserExceptionFactoryPtr&
agh::BadLoginException::ice_factory()
{
    return __F__agh__BadLoginException__Ptr;
}

class __F__agh__BadLoginException__Init
{
public:

    __F__agh__BadLoginException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::agh::BadLoginException", ::agh::BadLoginException::ice_factory());
    }

    ~__F__agh__BadLoginException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::agh::BadLoginException");
    }
};

static __F__agh__BadLoginException__Init __F__agh__BadLoginException__i;

#ifdef __APPLE__
extern "C" { void __F__agh__BadLoginException__initializer() {} }
#endif

agh::NoSuchTerminalException::~NoSuchTerminalException() throw()
{
}

static const char* __agh__NoSuchTerminalException_name = "agh::NoSuchTerminalException";

::std::string
agh::NoSuchTerminalException::ice_name() const
{
    return __agh__NoSuchTerminalException_name;
}

::Ice::Exception*
agh::NoSuchTerminalException::ice_clone() const
{
    return new NoSuchTerminalException(*this);
}

void
agh::NoSuchTerminalException::ice_throw() const
{
    throw *this;
}

void
agh::NoSuchTerminalException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::agh::NoSuchTerminalException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__write(__os);
#else
    ::agh::DirectoryException::__write(__os);
#endif
}

void
agh::NoSuchTerminalException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__read(__is, true);
#else
    ::agh::DirectoryException::__read(__is, true);
#endif
}

void
agh::NoSuchTerminalException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::NoSuchTerminalException was not generated with stream support";
    throw ex;
}

void
agh::NoSuchTerminalException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::NoSuchTerminalException was not generated with stream support";
    throw ex;
}

struct __F__agh__NoSuchTerminalException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::agh::NoSuchTerminalException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__agh__NoSuchTerminalException__Ptr = new __F__agh__NoSuchTerminalException;

const ::IceInternal::UserExceptionFactoryPtr&
agh::NoSuchTerminalException::ice_factory()
{
    return __F__agh__NoSuchTerminalException__Ptr;
}

class __F__agh__NoSuchTerminalException__Init
{
public:

    __F__agh__NoSuchTerminalException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::agh::NoSuchTerminalException", ::agh::NoSuchTerminalException::ice_factory());
    }

    ~__F__agh__NoSuchTerminalException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::agh::NoSuchTerminalException");
    }
};

static __F__agh__NoSuchTerminalException__Init __F__agh__NoSuchTerminalException__i;

#ifdef __APPLE__
extern "C" { void __F__agh__NoSuchTerminalException__initializer() {} }
#endif

agh::TerminalExistsException::~TerminalExistsException() throw()
{
}

static const char* __agh__TerminalExistsException_name = "agh::TerminalExistsException";

::std::string
agh::TerminalExistsException::ice_name() const
{
    return __agh__TerminalExistsException_name;
}

::Ice::Exception*
agh::TerminalExistsException::ice_clone() const
{
    return new TerminalExistsException(*this);
}

void
agh::TerminalExistsException::ice_throw() const
{
    throw *this;
}

void
agh::TerminalExistsException::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(::std::string("::agh::TerminalExistsException"), false);
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__write(__os);
#else
    ::agh::DirectoryException::__write(__os);
#endif
}

void
agh::TerminalExistsException::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->read(myId, false);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    DirectoryException::__read(__is, true);
#else
    ::agh::DirectoryException::__read(__is, true);
#endif
}

void
agh::TerminalExistsException::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::TerminalExistsException was not generated with stream support";
    throw ex;
}

void
agh::TerminalExistsException::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "exception agh::TerminalExistsException was not generated with stream support";
    throw ex;
}

struct __F__agh__TerminalExistsException : public ::IceInternal::UserExceptionFactory
{
    virtual void
    createAndThrow()
    {
        throw ::agh::TerminalExistsException();
    }
};

static ::IceInternal::UserExceptionFactoryPtr __F__agh__TerminalExistsException__Ptr = new __F__agh__TerminalExistsException;

const ::IceInternal::UserExceptionFactoryPtr&
agh::TerminalExistsException::ice_factory()
{
    return __F__agh__TerminalExistsException__Ptr;
}

class __F__agh__TerminalExistsException__Init
{
public:

    __F__agh__TerminalExistsException__Init()
    {
        ::IceInternal::factoryTable->addExceptionFactory("::agh::TerminalExistsException", ::agh::TerminalExistsException::ice_factory());
    }

    ~__F__agh__TerminalExistsException__Init()
    {
        ::IceInternal::factoryTable->removeExceptionFactory("::agh::TerminalExistsException");
    }
};

static __F__agh__TerminalExistsException__Init __F__agh__TerminalExistsException__i;

#ifdef __APPLE__
extern "C" { void __F__agh__TerminalExistsException__initializer() {} }
#endif

void
agh::__write(::IceInternal::BasicStream* __os, const ::agh::TerminalAddress* begin, const ::agh::TerminalAddress* end, ::agh::__U__Terminals)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
agh::__read(::IceInternal::BasicStream* __is, ::agh::Terminals& v, ::agh::__U__Terminals)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 4);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

void
agh::__addObject(const DirectoryPtr& p, ::IceInternal::GCCountMap& c)
{
    p->__addObject(c);
}

bool
agh::__usesClasses(const DirectoryPtr& p)
{
    return p->__usesClasses();
}

void
agh::__decRefUnsafe(const DirectoryPtr& p)
{
    p->__decRefUnsafe();
}

void
agh::__clearHandleUnsafe(DirectoryPtr& p)
{
    p.__clearHandleUnsafe();
}

void
IceProxy::agh::Directory::registerTerminal(const ::agh::TerminalAddress& address, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__agh__Directory__registerTerminal_name);
            __delBase = __getDelegate();
            ::IceDelegate::agh::Directory* __del = dynamic_cast< ::IceDelegate::agh::Directory*>(__delBase.get());
            __del->registerTerminal(address, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

void
IceProxy::agh::Directory::removeTerminal(const ::std::string& name, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__agh__Directory__removeTerminal_name);
            __delBase = __getDelegate();
            ::IceDelegate::agh::Directory* __del = dynamic_cast< ::IceDelegate::agh::Directory*>(__delBase.get());
            __del->removeTerminal(name, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::agh::TerminalAddress
IceProxy::agh::Directory::findTerminal(const ::std::string& name, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__agh__Directory__findTerminal_name);
            __delBase = __getDelegate();
            ::IceDelegate::agh::Directory* __del = dynamic_cast< ::IceDelegate::agh::Directory*>(__delBase.get());
            return __del->findTerminal(name, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::agh::Terminals
IceProxy::agh::Directory::findTerminals(const ::std::string& name, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__agh__Directory__findTerminals_name);
            __delBase = __getDelegate();
            ::IceDelegate::agh::Directory* __del = dynamic_cast< ::IceDelegate::agh::Directory*>(__delBase.get());
            return __del->findTerminals(name, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

::agh::Terminals
IceProxy::agh::Directory::getTerminals(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__agh__Directory__getTerminals_name);
            __delBase = __getDelegate();
            ::IceDelegate::agh::Directory* __del = dynamic_cast< ::IceDelegate::agh::Directory*>(__delBase.get());
            return __del->getTerminals(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, __cnt);
        }
    }
}

const ::std::string&
IceProxy::agh::Directory::ice_staticId()
{
    return ::agh::Directory::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::agh::Directory::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::agh::Directory);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::agh::Directory::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::agh::Directory);
}

bool
IceProxy::agh::operator==(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) == static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::agh::operator!=(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) != static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::agh::operator<(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return static_cast<const ::IceProxy::Ice::Object&>(l) < static_cast<const ::IceProxy::Ice::Object&>(r);
}

bool
IceProxy::agh::operator<=(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return l < r || l == r;
}

bool
IceProxy::agh::operator>(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return !(l < r) && !(l == r);
}

bool
IceProxy::agh::operator>=(const ::IceProxy::agh::Directory& l, const ::IceProxy::agh::Directory& r)
{
    return !(l < r);
}

void
IceDelegateM::agh::Directory::registerTerminal(const ::agh::TerminalAddress& address, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __agh__Directory__registerTerminal_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        address.__write(__os);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::agh::BadLoginException&)
            {
                throw;
            }
            catch(const ::agh::TerminalExistsException&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::agh::Directory::removeTerminal(const ::std::string& name, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __agh__Directory__removeTerminal_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(name);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::agh::NoSuchTerminalException&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::agh::TerminalAddress
IceDelegateM::agh::Directory::findTerminal(const ::std::string& name, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __agh__Directory__findTerminal_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(name);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::agh::NoSuchTerminalException&)
            {
                throw;
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::agh::TerminalAddress __ret;
        __ret.__read(__is);
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::agh::Terminals
IceDelegateM::agh::Directory::findTerminals(const ::std::string& name, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __agh__Directory__findTerminals_name, ::Ice::Normal, __context, __compress);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(name);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::agh::Terminals __ret;
        ::agh::__read(__is, __ret, ::agh::__U__Terminals());
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::agh::Terminals
IceDelegateM::agh::Directory::getTerminals(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__connection.get(), __reference.get(), __agh__Directory__getTerminals_name, ::Ice::Normal, __context, __compress);
    bool __ok = __og.invoke();
    try
    {
        ::IceInternal::BasicStream* __is = __og.is();
        if(!__ok)
        {
            try
            {
                __is->throwException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::agh::Terminals __ret;
        ::agh::__read(__is, __ret, ::agh::__U__Terminals());
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateD::agh::Directory::registerTerminal(const ::agh::TerminalAddress& address, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __agh__Directory__registerTerminal_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::agh::Directory* __servant = dynamic_cast< ::agh::Directory*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->registerTerminal(address, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

void
IceDelegateD::agh::Directory::removeTerminal(const ::std::string& name, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __agh__Directory__removeTerminal_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        try
        {
            ::agh::Directory* __servant = dynamic_cast< ::agh::Directory*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __servant->removeTerminal(name, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return;
    }
}

::agh::TerminalAddress
IceDelegateD::agh::Directory::findTerminal(const ::std::string& name, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __agh__Directory__findTerminal_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::agh::TerminalAddress __ret;
        try
        {
            ::agh::Directory* __servant = dynamic_cast< ::agh::Directory*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->findTerminal(name, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::agh::Terminals
IceDelegateD::agh::Directory::findTerminals(const ::std::string& name, const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __agh__Directory__findTerminals_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::agh::Terminals __ret;
        try
        {
            ::agh::Directory* __servant = dynamic_cast< ::agh::Directory*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->findTerminals(name, __current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::agh::Terminals
IceDelegateD::agh::Directory::getTerminals(const ::Ice::Context* __context)
{
    ::Ice::Current __current;
    __initCurrent(__current, __agh__Directory__getTerminals_name, ::Ice::Normal, __context);
    while(true)
    {
        ::IceInternal::Direct __direct(__current);
        ::agh::Terminals __ret;
        try
        {
            ::agh::Directory* __servant = dynamic_cast< ::agh::Directory*>(__direct.servant().get());
            if(!__servant)
            {
                ::Ice::OperationNotExistException __opEx(__FILE__, __LINE__);
                __opEx.id = __current.id;
                __opEx.facet = __current.facet;
                __opEx.operation = __current.operation;
                throw __opEx;
            }
            try
            {
                __ret = __servant->getTerminals(__current);
            }
            catch(const ::Ice::LocalException& __ex)
            {
                throw ::IceInternal::LocalExceptionWrapper(__ex, false);
            }
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
        return __ret;
    }
}

::Ice::ObjectPtr
agh::Directory::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __agh__Directory_ids[2] =
{
    "::Ice::Object",
    "::agh::Directory"
};

bool
agh::Directory::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__agh__Directory_ids, __agh__Directory_ids + 2, _s);
}

::std::vector< ::std::string>
agh::Directory::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__agh__Directory_ids[0], &__agh__Directory_ids[2]);
}

const ::std::string&
agh::Directory::ice_id(const ::Ice::Current&) const
{
    return __agh__Directory_ids[1];
}

const ::std::string&
agh::Directory::ice_staticId()
{
    return __agh__Directory_ids[1];
}

::IceInternal::DispatchStatus
agh::Directory::___registerTerminal(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::agh::TerminalAddress address;
    address.__read(__is);
    try
    {
        registerTerminal(address, __current);
    }
    catch(const ::agh::BadLoginException& __ex)
    {
        __os->write(__ex);
        return ::IceInternal::DispatchUserException;
    }
    catch(const ::agh::TerminalExistsException& __ex)
    {
        __os->write(__ex);
        return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
agh::Directory::___removeTerminal(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string name;
    __is->read(name);
    try
    {
        removeTerminal(name, __current);
    }
    catch(const ::agh::NoSuchTerminalException& __ex)
    {
        __os->write(__ex);
        return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
agh::Directory::___findTerminal(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string name;
    __is->read(name);
    try
    {
        ::agh::TerminalAddress __ret = findTerminal(name, __current);
        __ret.__write(__os);
    }
    catch(const ::agh::NoSuchTerminalException& __ex)
    {
        __os->write(__ex);
        return ::IceInternal::DispatchUserException;
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
agh::Directory::___findTerminals(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string name;
    __is->read(name);
    ::agh::Terminals __ret = findTerminals(name, __current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::agh::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::agh::__U__Terminals());
    }
    return ::IceInternal::DispatchOK;
}

::IceInternal::DispatchStatus
agh::Directory::___getTerminals(::IceInternal::Incoming&__inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __os = __inS.os();
    ::agh::Terminals __ret = getTerminals(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::agh::__write(__os, &__ret[0], &__ret[0] + __ret.size(), ::agh::__U__Terminals());
    }
    return ::IceInternal::DispatchOK;
}

static ::std::string __agh__Directory_all[] =
{
    "findTerminal",
    "findTerminals",
    "getTerminals",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "registerTerminal",
    "removeTerminal"
};

::IceInternal::DispatchStatus
agh::Directory::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__agh__Directory_all, __agh__Directory_all + 9, current.operation);
    if(r.first == r.second)
    {
        return ::IceInternal::DispatchOperationNotExist;
    }

    switch(r.first - __agh__Directory_all)
    {
        case 0:
        {
            return ___findTerminal(in, current);
        }
        case 1:
        {
            return ___findTerminals(in, current);
        }
        case 2:
        {
            return ___getTerminals(in, current);
        }
        case 3:
        {
            return ___ice_id(in, current);
        }
        case 4:
        {
            return ___ice_ids(in, current);
        }
        case 5:
        {
            return ___ice_isA(in, current);
        }
        case 6:
        {
            return ___ice_ping(in, current);
        }
        case 7:
        {
            return ___registerTerminal(in, current);
        }
        case 8:
        {
            return ___removeTerminal(in, current);
        }
    }

    assert(false);
    return ::IceInternal::DispatchOperationNotExist;
}

void
agh::Directory::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
agh::Directory::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
agh::Directory::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type agh::Directory was not generated with stream support";
    throw ex;
}

void
agh::Directory::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type agh::Directory was not generated with stream support";
    throw ex;
}

void 
agh::__patch__DirectoryPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::agh::DirectoryPtr* p = static_cast< ::agh::DirectoryPtr*>(__addr);
    assert(p);
    *p = ::agh::DirectoryPtr::dynamicCast(v);
    if(v && !*p)
    {
        ::Ice::UnexpectedObjectException e(__FILE__, __LINE__);
        e.type = v->ice_id();
        e.expectedType = ::agh::Directory::ice_staticId();
        throw e;
    }
}

bool
agh::operator==(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
agh::operator!=(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return static_cast<const ::Ice::Object&>(l) != static_cast<const ::Ice::Object&>(r);
}

bool
agh::operator<(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}

bool
agh::operator<=(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return l < r || l == r;
}

bool
agh::operator>(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return !(l < r) && !(l == r);
}

bool
agh::operator>=(const ::agh::Directory& l, const ::agh::Directory& r)
{
    return !(l < r);
}
