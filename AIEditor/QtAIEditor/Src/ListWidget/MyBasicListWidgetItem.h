#ifndef __MyBasicListWidgetItem_H
#define __MyBasicListWidgetItem_H

#include "QtIncAll.h"

class MyBasicListWidgetItem : public QListWidgetItem
{
public:
	MyBasicListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view = 0, int type = Type);
};

#endif