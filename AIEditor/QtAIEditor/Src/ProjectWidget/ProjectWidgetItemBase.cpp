#include "ProjectWidgetItemBase.h"

ProjectWidgetItemBase::ProjectWidgetItemBase()
{
	//m_self = this;
	m_itemData = new ProjectItemBase;
	m_type = 10;
	m_value.setValue(*this);	// 不能传地址，只能传递引用
}

bool ProjectWidgetItemBase::canConvert()
{
	if (m_value.canConvert<ProjectWidgetItemBase>())
	{
		return true;
	}

	return false;
}

void ProjectWidgetItemBase::delSelf()
{
	if (m_value.canConvert<ProjectWidgetItemBase>())
	{
		ProjectWidgetItemBase ret = m_value.value<ProjectWidgetItemBase>();
		delete m_self;
	}
}