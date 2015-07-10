#ifndef __MyBasicListWidgetItemLogicData_H
#define __MyBasicListWidgetItemLogicData_H

#include <vector>
#include "AIEditor.h"

BEGIN_NAMESPACE_AIEDITOR

class AIEDITOR_EXPORT MyBasicListWidgetItemLogicData
{
protected:
#include "PushWarn.h"
	std::string m_fullPathAndName;
#include "PopWarn.h"

public:
	MyBasicListWidgetItemLogicData();
	~MyBasicListWidgetItemLogicData();
};

END_NAMESPACE_AIEDITOR

#endif