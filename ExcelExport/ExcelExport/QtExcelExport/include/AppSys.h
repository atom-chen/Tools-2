#ifndef _APPDATA_H
#define _APPDATA_H

#include "Task.h"
#include "Singleton.h"
#include <string>
#include <QtCore>

#include "Platform.h"

QT_USE_NAMESPACE

class QComboBox;

BEGIN_NAMESPACE

class ExcelExport;
class Utils;
class System;
class WorkThread;

/**
 *@brief appdata
 */
class AppSys : public Singleton<AppSys>
{
protected:
	Task* m_task;			// main thread task, but only one thread
	ExcelExport* m_excelExport;
	WorkThread* m_pWorkThread;

	std::string m_outPath;
	std::string m_xmlFile;
	Utils* m_pUtils;
	System* m_pSystem;

public:
	AppSys();
	~AppSys();

	Task* getTask();
	void initData();
	ExcelExport* getExcelTbl();
	void startMultiPack();
	void startSinglePack();

	void setXml(std::string outpath, std::string xmlpath);
	bool isSetSolution();
	//void initThread(QThread* pthread);
	void startThread();

	void initCombo(QComboBox *comboBoxSolution);

	ExcelExport* getExcelExportPtr();
	WorkThread* getWorkThreadPtr();
	Utils* getUtilsPtr();
	System* getSystemPtr();
};

END_NAMESPACE

#define g_pAppSys AppSys::getSingletonPtr()
#define g_pExcelExport g_pAppSys->getExcelExportPtr()
#define g_pWorkThread g_pAppSys->getWorkThreadPtr()
#define g_pUtils g_pAppSys->getUtilsPtr()
#define g_pSystem g_pAppSys->getSystemPtr()

#endif