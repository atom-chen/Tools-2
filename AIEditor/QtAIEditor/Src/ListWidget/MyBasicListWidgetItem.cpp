#include "MyBasicListWidgetItem.h"

MyBasicListWidgetItem::MyBasicListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view, int type) : 
	QListWidgetItem(icon, text, view, type)
{

}

MyBasicListWidgetItem::~MyBasicListWidgetItem()
{
	delete(m_pItemData);
}

void MyBasicListWidgetItem::setItemData(MyBasicListWidgetItemData* pItemData)
{
	m_pItemData = pItemData;
}