
#ifndef DISPATCH_THREAD_H_
#define DISPATCH_THREAD_H_

#include <QThread>
#include <mutex>
#ifndef Q_MOC_RUN
#include <thread>
#include <condition_variable>
#endif

namespace Wt {

	class WQApplication;
	class WEvent;
	class DispatchThread;

	/*
	 * Help object used to dispatch an event into a Qt event loop.
	 */
	class DispatchObject : public QObject
	{
		Q_OBJECT

	public:
		DispatchObject(DispatchThread* thread);

		void propagateEvent();

	Q_SIGNALS:
		void doEvent();

	private Q_SLOTS:
		void onEvent();

	private:
		DispatchThread* thread_;
	};

	/*
	 * Thread in which all interaction with Qt objects is done.
	 *
	 * If constructed <i>withEventLoop</i>, then QThread::exec() is
	 * called, starting a new Qt event loop, and signal/slot events can be
	 * delivered within the event loop handling. Otherwise, plain thread
	 * synchronization is implemented.
	 */
	class DispatchThread : public QThread
	{
	public:
		DispatchThread(WQApplication* app, bool withEventLoop);

		virtual void run();

		std::unique_lock<std::mutex>* eventLock() { return eventLock_; }

		void notify(const WEvent& event);
		void destroy();
		bool exception() const { return exception_; }
		void resetException();

		void waitDone();

	private:
		WQApplication* app_;
		bool                            qtEventLoop_;
		std::unique_ptr<DispatchObject> dispatchObject_;
		const WEvent* event_;
		bool                            exception_;

		std::mutex                      doneMutex_;
		bool                            done_;
		std::condition_variable         doneCondition_;

		std::mutex                      newEventMutex_;
		bool                            newEvent_;
		std::condition_variable         newEventCondition_;
		std::unique_lock<std::mutex>* eventLock_;

		void doEvent();

		void signalDone();
		void myExec();
		void myPropagateEvent();

		friend class DispatchObject;
	};

}

#endif // DISPATCH_THREAD_H_
