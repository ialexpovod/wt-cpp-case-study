#ifndef QTOBJECT_H_
#define QTOBJECT_H_

#include <QThread>



class Dictionary;

/*! \class QtObject
 *  \brief A simple Qt object with sample signal and slot.
 *
 * This simple object class demonstrates that the Qt signal/slot
 * mechanism may be used alongside Wt's signal/slot mechanism.
 */
class QtObject : public QObject
{
	Q_OBJECT

public:
	QtObject(Dictionary* wt);

	void passGreet(const QString&);

Q_SIGNALS:
	void greet(const QString&);

public Q_SLOTS:
	void doGreet(const QString&);

private:
	Dictionary* wt_;
};

#endif // QTOBJECT_H_

