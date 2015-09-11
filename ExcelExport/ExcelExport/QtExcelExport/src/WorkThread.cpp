#include "WorkThread.h"
#include "AppSysPrerequisites.h"

BEGIN_NAMESPACE

WorkThread::WorkThread()
{
	m_running = false;
}

WorkThread::~WorkThread()
{

}

bool WorkThread::isRunning()
{
	return m_running;
}

void WorkThread::startThread()
{
	m_running = true;
	this->start();
}

void WorkThread::run()
{

}


void ExcelWorkThread::run()
{
	WorkThread::run();

	g_pAppSys->exportExcel();
	
	m_running = false;
}

CodeWorkThread::CodeWorkThread()
{
	m_bCsCode = false;
	m_bCppCode = false;
}

void CodeWorkThread::setCppCode(bool bCppCode)
{
	m_bCppCode = bCppCode;
}

bool CodeWorkThread::getCppCode()
{
	return m_bCppCode;
}

void CodeWorkThread::setCsCode(bool bCsCode)
{
	m_bCsCode = bCsCode;
}

bool CodeWorkThread::getCsCode()
{
	return m_bCsCode;
}

void CodeWorkThread::run()
{
	g_pUtils->Log(QStringLiteral("开始输出代码"));

	WorkThread::run();

	if (m_bCsCode)
	{
		g_pUtils->Log(QStringLiteral("开始输出 cs 代码"));
		g_pAppSys->exportCsCode();
	}
	if (m_bCppCode)
	{
		g_pUtils->Log(QStringLiteral("开始输出 c++ 代码"));
		g_pAppSys->exportCppCode();
	}

	g_pUtils->Log(QStringLiteral("结束输出代码"));

	m_running = false;
}

END_NAMESPACE