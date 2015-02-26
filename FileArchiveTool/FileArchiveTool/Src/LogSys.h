#ifndef __LogSys_H
#define __LogSys_H

#include <vector>
#include <string>
#include <boost/thread.hpp>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class LogDeviceBase;

class FILEARCHIVETOOL_EXPORT LogSys
{
protected:
	typedef std::vector<LogDeviceBase*> LogDeviceVec;
	typedef std::vector<LogDeviceBase*>::iterator LogDeviceVecIt;

	typedef std::vector<std::string> AsyncLogVec;
	typedef std::vector<std::string>::iterator AsyncLogVecIt;

protected:
	boost::thread::id* m_threadID;
	LogDeviceVec* m_pLogDeviceVec;		// 日志设备列表
	AsyncLogVec* m_pAsyncLogVec;		// 异步日志，这个地方存储的是 string ，因为异步日志可能延迟才能显示，否则内存不好释放，自己全部重新申请一块内存，然后自己释放
	boost::mutex* m_asyncLogLock;

public:
	LogSys();
	~LogSys();

	void log(const char* msg);
	void onTick();

	void regLogDevice(LogDeviceBase* pDev);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif