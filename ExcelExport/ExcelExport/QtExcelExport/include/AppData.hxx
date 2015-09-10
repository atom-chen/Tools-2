#ifndef _APPDATA_H
#define _APPDATA_H

#include "Task.hxx"
#include "Singleton.hxx"
#include <string>

class QThread;
class ExcelExport;
class QComboBox;

#include "Platform.hxx"
BEGIN_NAMESPACE

/**
 *@brief appdata
 */
class AppData : public Singleton<AppData>
{
protected:
	Task* m_task;			// main thread task, but only one thread
	ExcelExport* m_excelExport;
	QThread* m_pthread;

	string m_outPath;
	string m_xmlFile;

public:
	AppData();
	~AppData();

	Task* getTask();
	void initData();
	ExcelExport* getExcelTbl();
	void startMultiPack();
	void startSinglePack();

	void setXml(string outpath, string xmlpath);
	bool isSetSolution();
	void initThread(QThread* pthread);
	void startThread();

	void initCombo(QComboBox *comboBoxSolution);
};

END_NAMESPACE

#endif