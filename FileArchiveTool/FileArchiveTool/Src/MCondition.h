#ifndef __MCondition_H
#define __MCondition_H

#include "Prerequisites.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT MCondition
{
protected:
	boost::mutex* m_NotifyLock;
	boost::condition* m_pNotifyCond;
	bool m_canEnterWait;  // 是否可以进入等待

public:
	MCondition();
	virtual ~MCondition();

	bool canEnterWait();
	void wait();
	void notifyAll();
	void notifyOne();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif