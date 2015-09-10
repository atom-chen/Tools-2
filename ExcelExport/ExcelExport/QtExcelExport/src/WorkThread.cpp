#include "WorkThread.hxx"
#include "Tools.hxx"
#include "AppData.hxx"

void WorkThread::run()
{
	Tools::getSingletonPtr()->setRunning(true);
	if(AppData::getSingletonPtr()->isSetSolution())
	{
		AppData::getSingletonPtr()->startMultiPack();
	}
	else
	{
		//m_excelTbl->convExcel2Tbl();
		AppData::getSingletonPtr()->startSinglePack();
	}
	Tools::getSingletonPtr()->setRunning(false);
}

//void WorkThread::setParam(ExcelTbl* para)
//{
//	m_excelTbl = para;
//}