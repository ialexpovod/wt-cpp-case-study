
#include <iostream>
#include "WQApplication.h"
#include "DispatchThread.h"
#include <Wt/WLogger.h>

namespace Wt {

    WQApplication::WQApplication(const WEnvironment& env, bool withEventLoop)
        : WApplication(env),
        withEventLoop_(withEventLoop),
        finalized_(false),
        recursiveEvent_(false)
    { }

    void WQApplication::initialize()
    {
        log("debug") << "WQApplication: initialize()";
        WApplication::initialize();

        create();
    }

    void WQApplication::finalize()
    {
        log("debug") << "WQApplication: finalize()";
        WApplication::finalize();

        destroy();
        thread_->destroy();

        finalized_ = true;
    }

    void WQApplication::notify(const WEvent& e)
    {
        if (!thread_) {
            log("debug") << "WQApplication: starting thread";
            thread_ = std::make_unique<DispatchThread>(this, withEventLoop_);
            thread_->start();
            thread_->waitDone();
        }

        if (recursiveEvent_) {
            /* This could be from within a recursive event loop */
            log("debug") << "WQApplication: notify() from within QThread";
            realNotify(e);
            return;
        }

        if (e.eventType() == EventType::Resource && recursiveEvent_) {
            /*
             * We do not relay resource events while blocked in a recursive event
             * loop, since these will not unlock a recursive event loop and
             * thus we cannot communicate with the private thread when it's
             * blocked in a recursive event loop
             */
            log("debug") << "WQApplication: notify() for resource during recursive "
                << "event, handling in thread pool.";
            realNotify(e);
            return;
        }

        log("debug") << "WQApplication: notifying thread";
        thread_->notify(e);

        if (thread_->exception()) {
            thread_->resetException();
            throw std::runtime_error("WQApplication: rethrowing exception");
        }

        if (finalized_) {
            log("debug") << "WQApplication: joining thread";
            thread_->wait();
            thread_.reset();
        }
    }

    void WQApplication::realNotify(const WEvent& e)
    {
        WApplication::notify(e);
    }

    void WQApplication::waitForEvent()
    {
        log("debug") << "WQApplication: [thread] waitForEvent()";

        recursiveEvent_ = true;

        if (thread_->eventLock())
            thread_->eventLock()->unlock();

        try {
            WApplication::waitForEvent();
        }
        catch (...) {
            if (thread_->eventLock())
                thread_->eventLock()->lock();
            recursiveEvent_ = false;
            throw;
        }

        if (thread_->eventLock())
            thread_->eventLock()->lock();
        recursiveEvent_ = false;

        log("debug") << "WQApplication: [thread] returning from waitForEvent()";
    }

    WString toWString(const QString& s)
    {
        return Wt::utf8((const char*)s.toUtf8());
    }

    QString toQString(const WString& s)
    {
        return QString::fromUtf8(s.toUTF8().c_str());
    }

}
