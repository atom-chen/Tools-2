#ifndef __MyBasicListWidgetItemData_H
#define __MyBasicListWidgetItemData_H

#include "QtIncAll.h"
#include "MyBasicListWidgetItemLogicData.h"

class MyBasicListWidgetItemData : public MyBasicListWidgetItemLogicData
{
public:
	QVariant m_value;

public:
	MyBasicListWidgetItemData();
	~MyBasicListWidgetItemData();
};

Q_DECLARE_METATYPE(MyBasicListWidgetItemData)

#endif