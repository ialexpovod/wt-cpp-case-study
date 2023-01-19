#ifndef HELLO_APPLICATION_H_
#define HELLO_APPLICATION_H_

#include "WQApplication.h"

class QtObject;
class QString;

using namespace Wt;

namespace Wt {
	class WLineEdit;
	class WText;
}

/*! \class HelloApplication
 *  \brief The 'hello' application modified to use QtCore
 *
 * A sample application that uses objects from the QtCore library.
 */
class Dictionary : public WQApplication
{
public:
	Dictionary(const WEnvironment& env);

	void doGreet(const QString&);

	virtual void create();
	virtual void destroy();

private:
	WLineEdit* nameEdit_;
	WText* greeting_;

	std::unique_ptr<QtObject>  qtSender_, qtReceiver_;

	void propagateGreet();
};

#endif // HELLO_APPLICATION_H_
