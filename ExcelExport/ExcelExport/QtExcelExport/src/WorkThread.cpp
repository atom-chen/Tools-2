#include "WorkThread.h"
#include "AppSysPrerequisites.h"

void WorkThread::run()
{
	g_pUtils->setRunning(true);
	if(g_pAppSys->isSetSolution())
	{
		g_pAppSys->startMultiPack();
	}
	else
	{
		//m_excelTbl->convExcel2Tbl();
		g_pAppSys->startSinglePack();
	}
	g_pUtils->setRunning(false);
}

//void WorkThread::setParam(ExcelTbl* para)
//{
//	m_excelTbl = para;
//}