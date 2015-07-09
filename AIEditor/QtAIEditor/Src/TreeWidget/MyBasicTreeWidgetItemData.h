#ifndef __MyBasicTreeWidgetItemData_H
#define __MyBasicTreeWidgetItemData_H

#include <QtCore/QtCore>

#include "ProjectItemBase.h"

class MyBasicTreeWidgetItemData
{
public:
	QVariant m_value;
	MyBasicTreeWidgetItemData* m_self;

protected:
	ProjectItemBase* m_itemData;
	int m_type;

public:
	MyBasicTreeWidgetItemData();
	bool canConvert();
	void delSelf();
};

Q_DECLARE_METATYPE(MyBasicTreeWidgetItemData)

#endif