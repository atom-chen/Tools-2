#include "ThreadPool.h"
#include "TaskThread.h"
#include "FileArchiveToolSys.h"
#include "ITaskQueue.h"
#include "TaskQueue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ThreadPool::ThreadPool(uint32 numThread)
{
	m_numThread = numThread;
	m_numThread = 1;
	m_pThreadVec = new std::vector<TaskThread*>(m_numThread);
	//for (uint32 idx = 0; idx < m_numThread; ++idx)
	//{
	//	// ���캯����ǧ��Ҫ����ȫ�ֱ�������Ϊ���ʱ��ȫ�ֱ������ܻ��ڹ�����
	//	(*m_pThreadVec)[idx] = new TaskThread(FileArchiveToolSysDef->getTaskQueuePtr());
	//	(*m_pThreadVec)[idx]->Start();
	//}
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::instanceThread()
{
	for (uint32 idx = 0; idx < m_numThread; ++idx)
	{
		(*m_pThreadVec)[idx] = new TaskThread(FileArchiveToolSysDef->getTaskQueuePtr());
		(*m_pThreadVec)[idx]->Start();
	}
}

void ThreadPool::wait()
{
	for (auto thread : *m_pThreadVec)
	{
		thread->setExitFlag(true);		// ���ý�����ʶ
		thread->notifyNotEmpty();		// ֪ͨһ�Σ���ֹ�߳��ڵȴ���
		thread->Wait();
	}

	for (auto thread : *m_pThreadVec)
	{
		delete thread;
	}

	m_pThreadVec->clear();
	m_pThreadVec = nullptr;
}

void ThreadPool::notifyIdleThread()
{
	for (auto thread : *m_pThreadVec)
	{
		if (thread->notifySelf())       // �������ĳ���߳̾��˳������һ����û�л��ѣ�˵����ǰ�̶߳��Ƚ�æ����Ҫ�ȴ�
		{
			break;
		}
	}
}

END_NAMESPACE_FILEARCHIVETOOL