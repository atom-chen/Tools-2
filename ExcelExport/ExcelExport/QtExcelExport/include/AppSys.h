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
class ExcelWorkThread;
class CodeWorkThread;

/**
 *@brief appdata
 */
class AppSys : public Singleton<AppSys>
{
protected:
	Task* m_task;			// main thread task, but only one thread
	ExcelExport* m_excelExport;
	ExcelWorkThread* m_pExcelWorkThread;
	CodeWorkThread* m_pCodeWorkThread;

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

	void initCombo(QComboBox *comboBoxSolution);
	void exportCppCode();
	void exportCsCode();

	ExcelExport* getExcelExportPtr();
	ExcelWorkThread* getExcelWorkThreadPtr();
	CodeWorkThread* getCodeWorkThreadPtr();
	Utils* getUtilsPtr();
	System* getSystemPtr();
};

END_NAMESPACE

#define g_pAppSys AppSys::getSingletonPtr()
#define g_pExcelExport g_pAppSys->getExcelExportPtr()
#define g_pCodeWorkThread g_pAppSys->getCodeWorkThreadPtr()
#define g_pExcelWorkThread g_pAppSys->getExcelWorkThreadPtr()
#define g_pUtils g_pAppSys->getUtilsPtr()
#define g_pSystem g_pAppSys->getSystemPtr()

#endif