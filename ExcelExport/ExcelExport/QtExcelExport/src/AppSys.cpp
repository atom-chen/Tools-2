#include <cstring>
#include <QtGui/QtGui>
#include <QtWidgets>
#include "ExcelExport.h"
#include "Task.h"
#include "Utils.h"
#include "AppSys.h"
#include "MemLeakCheck.h"

template<> AppSys* Singleton<AppSys>::msSingleton = 0;

AppSys::AppSys()
{
	m_pUtils = new Utils();
}

AppSys::~AppSys()
{
	delete m_pUtils;
}

Task* AppSys::getTask()
{
	return m_task;
}

void AppSys::initData()
{
	m_task = new Task();
	m_excelExport = new ExcelExport();
	m_task->readXML();
}

ExcelExport* AppSys::getExcelTbl()
{
	return m_excelExport;
}

// start Multi
void AppSys::startMultiPack()
{
	// 导出所有的表
	std::vector<Table*>& tableList = m_task->getTableList();

	std::vector<Table*>::iterator tableIteVecBegin = tableList.begin();
	std::vector<Table*>::iterator tableIteVecEnd = tableList.end();
	for (; tableIteVecBegin != tableIteVecEnd; ++tableIteVecBegin)
	{
		if ((*tableIteVecBegin)->m_bExportTable)
		{
			m_excelExport->exportExcelByTable((*tableIteVecBegin));
		}
	}

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

void AppSys::setXml(string outpath, string xmlpath)
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

void AppSys::initThread(QThread* pthread)
{
	m_pthread = pthread;
}

void AppSys::startThread()
{
	m_pthread->start();
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

Utils* AppSys::getUtilsPtr()
{
	return m_pUtils;
}