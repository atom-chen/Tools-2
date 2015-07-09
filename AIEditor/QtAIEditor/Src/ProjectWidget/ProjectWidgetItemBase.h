#ifndef __ProjectWidgetItemBase_H
#define __ProjectWidgetItemBase_H

#include <QtCore/QtCore>

#include "ProjectItemBase.h"

class ProjectWidgetItemBase
{
public:
	QVariant m_value;
	ProjectWidgetItemBase* m_self;

protected:
	ProjectItemBase* m_itemData;
	int m_type;

public:
	ProjectWidgetItemBase();
	bool canConvert();
	void delSelf();
};

Q_DECLARE_METATYPE(ProjectWidgetItemBase)

#endif // __ProjectWidgetItemBase_H