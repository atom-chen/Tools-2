#ifndef __CodeExport_h
#define __CodeExport_h

#include <string>
#include <QtCore>	// QMutex
#include "MemLeakCheck.h"
#include "Platform.h"


BEGIN_NAMESPACE

class CodeExport
{
protected:
	std::string m_xmlPath;		// 绝对路径的文件名字
	std::string m_tblPath;		// tbl 输出路径
	QMutex m_mutex;

public:
	CodeExport();
	~CodeExport();
	void setXmlPath(std::string file);
	void setOutputPath(std::string path);

	bool exportCsCode();
	bool exportCppCode();
};

END_NAMESPACE

#endif