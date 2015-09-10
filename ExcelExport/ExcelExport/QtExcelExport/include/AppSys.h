#ifndef _APPDATA_H
#define _APPDATA_H

#include "Task.h"
#include "Singleton.h"
#include <string>

#include "Platform.h"

BEGIN_NAMESPACE

class QThread;
class ExcelExport;
class QComboBox;
class Utils;

/**
 *@brief appdata
 */
class AppSys : public Singleton<AppSys>
{
protected:
	Task* m_task;			// main thread task, but only one thread
	ExcelExport* m_excelExport;
	QThread* m_pthread;

	std::string m_outPath;
	std::string m_xmlFile;
	Utils* m_pUtils;

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
	void initThread(QThread* pthread);
	void startThread();

	void initCombo(QComboBox *comboBoxSolution);

	Utils* getUtilsPtr();
};

END_NAMESPACE

#define g_pAppSys AppSys::getSingletonPtr()
#define g_pUtils AppSys::getSingletonPtr()->getUtilsPtr()

#endif