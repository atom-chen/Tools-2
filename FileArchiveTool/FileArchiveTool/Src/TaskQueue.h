#ifndef __TaskQueue_H
#define __TaskQueue_H

#include <boost/thread.hpp>
#include <queue>
class ITask;

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT TaskQueue
{
protected:
	std::queue<ITask*>* m_pTaskQueue;
	std::queue<ITask*>* m_pResultQueue;

	boost::mutex* m_taskLock;
	boost::mutex* m_resultLock;

public:
	TaskQueue();
	~TaskQueue();

	void addTask(ITask* task);
	ITask* removeTask();

	void addResult(ITask* task);
	ITask* removeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif