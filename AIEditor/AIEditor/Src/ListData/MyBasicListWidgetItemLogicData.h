#ifndef __MyBasicListWidgetItemLogicData_H
#define __MyBasicListWidgetItemLogicData_H

#include <string>
#include "AIEditor.h"

BEGIN_NAMESPACE_AIEDITOR

class AIEDITOR_EXPORT MyBasicListWidgetItemLogicData
{
protected:
#include "PushWarn.h"
	std::string m_fullPathAndName;
#include "PopWarn.h"
	bool m_bFile;		// 是否是文件

public:
	MyBasicListWidgetItemLogicData();
	~MyBasicListWidgetItemLogicData();

	void setFullPath(std::string path);
	std::string getFullPath();

	void setBFile(bool bFile_);
	bool getBFile();
};

END_NAMESPACE_AIEDITOR

#endif