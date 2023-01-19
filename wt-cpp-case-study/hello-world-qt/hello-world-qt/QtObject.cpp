#include "hello.h"
#include "QtObject.h"

QtObject::QtObject(Dictionary* wt)
	: wt_(wt)
{ }

void QtObject::passGreet(const QString& name)
{
	Q_EMIT greet(name);
}

void QtObject::doGreet(const QString& name)
{
	wt_->doGreet(name);
}
