#include "TaskQueue.h"
#include "TaskThread.h"
#include "ITask.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

TaskQueue::TaskQueue()
{
	m_pTaskQueue = new std::queue<ITask*>;
	m_pResultQueue = new std::queue<ITask*>;

	m_taskLock = new boost::mutex;
	m_resultLock = new boost::mutex;

	//m_pTaskThread = new TaskThread(this);
	//m_pTaskThread->Start();
}

TaskQueue::~TaskQueue()
{
	delete m_pTaskQueue;
	delete m_pResultQueue;

	delete m_taskLock;
	delete m_resultLock;
}

void TaskQueue::addTask(ITask* task)
{
	boost::lock_guard<boost::mutex> lock(*m_taskLock);
	m_pTaskQueue->push(task);
	if (m_pTaskQueue->size() == 1)	// 如果只有一个，可能任务线程处于阻塞状态，需要唤醒
	{
		m_pTaskThread->notifyNotEmpty();
	}
}

ITask* TaskQueue::removeTask()
{
	ITask* ret = nullptr;
	if (m_pTaskQueue->size())
	{
		boost::lock_guard<boost::mutex> lock(*m_taskLock);
		ret = m_pTaskQueue->front();
		m_pTaskQueue->pop();
	}

	return ret;
}

void TaskQueue::addResult(ITask* task)
{
	boost::lock_guard<boost::mutex> lock(*m_resultLock);
	m_pResultQueue->push(task);
}

ITask* TaskQueue::removeResult()
{
	ITask* ret = nullptr;
	if (m_pResultQueue->size())
	{
		boost::lock_guard<boost::mutex> lock(*m_resultLock);
		ret = m_pResultQueue->front();
		m_pResultQueue->pop();
	}

	return ret;
}

void TaskQueue::endTask()
{
	m_pTaskThread->setExitFlag(true);		// 设置结束标识
	m_pTaskThread->notifyNotEmpty();		// 通知一次，防止线程在等待中
	m_pTaskThread->Wait();					// 等待线程结束
}

void TaskQueue::onTick()
{
	ITask* task = removeResult();
	task->exeResult();
	delete task;
}

END_NAMESPACE_FILEARCHIVETOOL