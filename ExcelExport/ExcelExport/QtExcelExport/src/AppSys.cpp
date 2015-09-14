#include "AppSys.h"
#include <string.h>
#include <QtGui/QtGui>
#include <QtWidgets>
#include "ExcelExport.h"
#include "Task.h"
#include "Utils.h"
#include "System.h"
#include "WorkThread.h"
#include "MemLeakCheck.h"
#include "CodeExport.h"

BEGIN_NAMESPACE

template<> AppSys* Singleton<AppSys>::msSingleton = 0;

AppSys::AppSys()
{
	m_pUtils = new Utils;
	m_pSystem = new System;
	m_task = new Task;
	m_excelExport = new ExcelExport;
	m_pExcelWorkThread = new ExcelWorkThread;
	m_pCodeWorkThread = new CodeWorkThread;
	m_codeExport = new CodeExport;
}

AppSys::~AppSys()
{
	delete m_pUtils;
	delete m_pSystem;
	delete m_task;
	delete m_excelExport;
	delete m_pExcelWorkThread;
	delete m_pCodeWorkThread;
	delete m_codeExport;
}

Task* AppSys::getTask()
{
	return m_task;
}

void AppSys::initData()
{
	m_task->readXML();
}

ExcelExport* AppSys::getExcelTbl()
{
	return m_excelExport;
}

void AppSys::exportExcel()
{
	if (isSetSolution())
	{
		startMultiPack();
	}
	else
	{
		startSinglePack();
	}
}

// start Multi
void AppSys::startMultiPack()
{
	// 导出所有的表
	//std::vector<Table*>& tableList = m_task->getTableList();

	//std::vector<Table*>::iterator tableIteVecBegin = tableList.begin();
	//std::vector<Table*>::iterator tableIteVecEnd = tableList.end();
	//for (; tableIteVecBegin != tableIteVecEnd; ++tableIteVecBegin)
	//{
	//	if ((*tableIteVecBegin)->m_bExportTable)
	//	{
	//		(*tableIteVecBegin)->exportExcel();
	//	}
	//}

	m_task->getSolution()->exportExcel();

	if (m_task->getSolution()->getCmd().length())
	{
		QProcess::startDetached(m_task->getSolution()->getCmd().c_str(), QStringList());
	}
}

// start single
void AppSys::startSinglePack()
{
	m_excelExport->exportExcel();
}

void AppSys::exportCppCode()
{
	//std::vector<Table*>& tableList = m_task->getTableList();

	//std::vector<Table*>::iterator tableIteVecBegin = tableList.begin();
	//std::vector<Table*>::iterator tableIteVecEnd = tableList.end();
	//for (; tableIteVecBegin != tableIteVecEnd; ++tableIteVecBegin)
	//{
	//	if ((*tableIteVecBegin)->m_bExportTable)
	//	{
	//		(*tableIteVecBegin)->exportCppCode();
	//	}
	//}

	if (isSetSolution())
	{
		m_task->getSolution()->exportCppCode();
	}
	else
	{
		m_codeExport->exportCppCode();
	}
}

void AppSys::exportCsCode()
{
	//std::vector<Table*>& tableList = m_task->getTableList();

	//std::vector<Table*>::iterator tableIteVecBegin = tableList.begin();
	//std::vector<Table*>::iterator tableIteVecEnd = tableList.end();
	//for (; tableIteVecBegin != tableIteVecEnd; ++tableIteVecBegin)
	//{
	//	if ((*tableIteVecBegin)->m_bExportTable)
	//	{
	//		(*tableIteVecBegin)->exportCsCode();
	//	}
	//}

	if (isSetSolution())
	{
		m_task->getSolution()->exportCsCode();
	}
	else
	{
		m_codeExport->exportCsCode();
	}
}

void AppSys::setXml(std::string outpath, std::string xmlpath)
{
	m_outPath = outpath;
	m_xmlFile = xmlpath;

	m_excelExport->setXmlPath(m_xmlFile.c_str());
	m_excelExport->setOutputPath(m_outPath.c_str());
}

bool AppSys::isSetSolution()
{
	return (0 == m_outPath.length() && 0 == m_xmlFile.length());
}

void AppSys::initCombo(QComboBox *comboBoxSolution)
{
	//QString tmp;
	//std::vector<Solution*>::iterator ite;
	//for (ite = m_task.getSolutionLst().begin(); ite != m_task.getSolutionLst().end(); ++ite)
	//{
	//	//comboBoxSolution->addItem(QString::fromLocal8Bit((ite->getName().c_str())));
	//	tmp = g_pUtils->GBKChar2UNICODEStr((*ite)->getName().c_str());
	//	comboBoxSolution->addItem(tmp);
	//}
}

ExcelExport* AppSys::getExcelExportPtr()
{
	return m_excelExport;
}

ExcelWorkThread* AppSys::getExcelWorkThreadPtr()
{
	return m_pExcelWorkThread;
}

CodeWorkThread* AppSys::getCodeWorkThreadPtr()
{
	return m_pCodeWorkThread;
}

Utils* AppSys::getUtilsPtr()
{
	return m_pUtils;
}

System* AppSys::getSystemPtr()
{
	return m_pSystem;
}

END_NAMESPACE