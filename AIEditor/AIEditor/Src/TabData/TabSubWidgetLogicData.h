#ifndef __TabSubWidgetLogicData_H
#define __TabSubWidgetLogicData_H

#include <string>
#include "AIEditor.h"

BEGIN_NAMESPACE_AIEDITOR

class AIEDITOR_EXPORT TabSubWidgetLogicData
{
protected:
#include "PushWarn.h"
	std::string m_fullPathAndName;
#include "PopWarn.h"

public:
	TabSubWidgetLogicData();
	~TabSubWidgetLogicData();

	void setFullPath(std::string path);
	std::string getFullPath();
};

END_NAMESPACE_AIEDITOR

#endif