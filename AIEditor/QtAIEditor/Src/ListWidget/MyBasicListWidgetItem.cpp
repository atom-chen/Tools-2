#include "MyBasicListWidgetItem.h"
#include "MyBasicListWidgetItemData.h"

MyBasicListWidgetItem::MyBasicListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view, int type) : 
	QListWidgetItem(icon, text, view, type)
{
	m_pItemData = nullptr;
}

MyBasicListWidgetItem::~MyBasicListWidgetItem()
{
	delete(m_pItemData);
}

void MyBasicListWidgetItem::setItemData(MyBasicListWidgetItemData* pItemData)
{
	m_pItemData = pItemData;
}

MyBasicListWidgetItemData* MyBasicListWidgetItem::getItemData()
{
	return m_pItemData;
}