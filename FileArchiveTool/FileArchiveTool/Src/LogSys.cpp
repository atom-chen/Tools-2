#include "LogSys.h"
#include "LogDeviceBase.h"
#include "Thread.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

LogSys::LogSys()
{
	m_pLogDeviceVec = new LogDeviceVec;
	m_pAsyncLogVec = new AsyncLogVec;
	m_threadID = new boost::thread::id;
	m_asyncLogLock = new boost::mutex;
	*m_threadID = Thread::currentId();
}

LogSys::~LogSys()
{
	delete m_pLogDeviceVec;
	delete m_pAsyncLogVec;
	delete m_asyncLogLock;
	delete m_threadID;
}

void LogSys::log(const char* msg)
{
	if (*m_threadID == boost::thread::id())		// 如果是主线程中调用
	{
		LogDeviceVecIt itBegin, itEnd;
		itBegin = m_pLogDeviceVec->begin();
		itEnd = m_pLogDeviceVec->end();

		for (; itBegin != itEnd; ++itBegin)
		{
			(*itBegin)->log(msg);
		}
	}
	else
	{
		boost::lock_guard<boost::mutex> lock(*m_asyncLogLock);
		m_pAsyncLogVec->push_back(msg);
	}
}

void LogSys::onTick()
{
	boost::lock_guard<boost::mutex> lock(*m_asyncLogLock);

	LogDeviceVecIt itBegin, itEnd;
	itBegin = m_pLogDeviceVec->begin();
	itEnd = m_pLogDeviceVec->end();

	for (; itBegin != itEnd; ++itBegin)
	{
		AsyncLogVecIt itBeginLog, itEndLog;
		itBeginLog = m_pAsyncLogVec->begin();
		itEndLog = m_pAsyncLogVec->end();

		for (; itBeginLog != itEndLog; ++itBeginLog)
		{
			(*itBegin)->log(itBeginLog->c_str());
		}
	}

	m_pAsyncLogVec->clear();
}

void LogSys::regLogDevice(LogDeviceBase* pDev)
{
	m_pLogDeviceVec->push_back(pDev);
}

END_NAMESPACE_FILEARCHIVETOOL