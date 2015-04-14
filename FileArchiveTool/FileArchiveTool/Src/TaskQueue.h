#ifndef __TaskQueue_H
#define __TaskQueue_H

#include <boost/thread.hpp>
#include <queue>
#include "ITaskQueue.h"

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ITask;
class TaskThread;

class FILEARCHIVETOOL_EXPORT TaskQueue : public ITaskQueue
{
protected:
	std::queue<ITask*>* m_pTaskQueue;
	std::queue<ITask*>* m_pResultQueue;

	boost::mutex* m_taskLock;
	boost::mutex* m_resultLock;

	//TaskThread* m_pTaskThread;

public:
	TaskQueue();
	~TaskQueue();

	void addTask(ITask* task);
	virtual ITask* removeTask();

	virtual void addResult(ITask* task);
	ITask* removeResult();

	void endTask();
	void onTick();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif