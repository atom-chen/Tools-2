#ifndef __MyBasicTreeWidgetItemData_H
#define __MyBasicTreeWidgetItemData_H

#include <QtCore/QtCore>

#include "MyBasicTreeWidgetItemLogicData.h"

class MyBasicTreeWidgetItemData
{
public:
	QVariant m_value;
	MyBasicTreeWidgetItemData* m_self;

protected:
	MyBasicTreeWidgetItemLogicData* m_itemData;
	int m_type;

public:
	MyBasicTreeWidgetItemData();
	bool canConvert();
	void delSelf();
};

Q_DECLARE_METATYPE(MyBasicTreeWidgetItemData)

#endif