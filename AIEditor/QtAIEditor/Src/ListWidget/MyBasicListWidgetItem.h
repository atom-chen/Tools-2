#ifndef __MyBasicListWidgetItem_H
#define __MyBasicListWidgetItem_H

#include "QtIncAll.h"

class MyBasicListWidgetItemData;

class MyBasicListWidgetItem : public QListWidgetItem
{
protected:
	MyBasicListWidgetItemData* m_pItemData;

public:
	MyBasicListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view = 0, int type = Type);
	~MyBasicListWidgetItem();
	void setItemData(MyBasicListWidgetItemData* pItemData);
};

#endif