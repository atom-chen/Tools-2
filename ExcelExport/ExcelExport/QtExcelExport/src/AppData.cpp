#include <cstring>
#include <QtGui/QtGui>
#include <QtWidgets>
#include "ExcelExport.hxx"
#include "Task.hxx"
#include "Tools.hxx"
#include "AppData.hxx"

#include "MemLeakCheck.hxx"

template<> AppData* Singleton<AppData>::msSingleton = 0;

AppData::AppData()
{
	
}

AppData::~AppData()
{

}

Task* AppData::getTask()
{
	return m_task;
}

void AppData::initData()
{
	m_task = new Task();
	m_excelExport = new ExcelExport();
	m_task->readXML();
}

ExcelExport* AppData::getExcelTbl()
{
	return m_excelExport;
}

// start Multi
void AppData::startMultiPack()
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
void AppData::startSinglePack()
{
	m_excelExport->exportExcel();
}

void AppData::setXml(string outpath, string xmlpath)
{
	m_outPath = outpath;
	m_xmlFile = xmlpath;

	m_excelExport->setXmlPath(m_xmlFile.c_str());
	m_excelExport->setOutputPath(m_outPath.c_str());
}

bool AppData::isSetSolution()
{
	return (0 == m_outPath.length() && 0 == m_xmlFile.length());
}

void AppData::initThread(QThread* pthread)
{
	m_pthread = pthread;
}

void AppData::startThread()
{
	m_pthread->start();
}

void AppData::initCombo(QComboBox *comboBoxSolution)
{
	//QString tmp;
	//std::vector<Solution*>::iterator ite;
	//for (ite = m_task.getSolutionLst().begin(); ite != m_task.getSolutionLst().end(); ++ite)
	//{
	//	//comboBoxSolution->addItem(QString::fromLocal8Bit((ite->getName().c_str())));
	//	tmp = Tools::getSingletonPtr()->GBKChar2UNICODEStr((*ite)->getName().c_str());
	//	comboBoxSolution->addItem(tmp);
	//}
}