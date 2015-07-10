#include "MyBasicTreeWidgetItemData.h"

MyBasicTreeWidgetItemData::MyBasicTreeWidgetItemData()
{
	//m_self = this;
	m_itemData = new MyBasicTreeWidgetItemLogicData;
	m_type = 10;
	m_value.setValue(*this);	// 不能传地址，只能传递引用
}

bool MyBasicTreeWidgetItemData::canConvert()
{
	if (m_value.canConvert<MyBasicTreeWidgetItemData>())
	{
		return true;
	}

	return false;
}

void MyBasicTreeWidgetItemData::delSelf()
{
	if (m_value.canConvert<MyBasicTreeWidgetItemData>())
	{
		MyBasicTreeWidgetItemData ret = m_value.value<MyBasicTreeWidgetItemData>();
		delete m_self;
	}
}