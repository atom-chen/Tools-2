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
	LogDeviceVec* m_pLogDeviceVec;		// ��־�豸�б�
	AsyncLogVec* m_pAsyncLogVec;		// �첽��־������ط��洢���� string ����Ϊ�첽��־�����ӳٲ�����ʾ�������ڴ治���ͷţ��Լ�ȫ����������һ���ڴ棬Ȼ���Լ��ͷ�
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