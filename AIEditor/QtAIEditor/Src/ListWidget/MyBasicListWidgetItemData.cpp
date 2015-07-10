#include "MyBasicListWidgetItemData.h"

MyBasicListWidgetItemData::MyBasicListWidgetItemData()
{
	//m_value.setValue(this);
	m_value = QVariant::fromValue<MyBasicListWidgetItemData>(*this);
}

MyBasicListWidgetItemData::~MyBasicListWidgetItemData()
{

}