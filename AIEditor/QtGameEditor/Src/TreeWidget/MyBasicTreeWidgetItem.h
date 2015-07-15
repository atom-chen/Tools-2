#ifndef __MyBasicTreeWidgetItem_H
#define __MyBasicTreeWidgetItem_H

#include "QtIncAll.h"

class MyBasicTreeWidgetItem : public QTreeWidgetItem
{
protected:

public:
	MyBasicTreeWidgetItem(QTreeWidget *view, const QStringList &strings, int type = Type);
	MyBasicTreeWidgetItem(QTreeWidgetItem *parent, const QStringList &strings, int type = Type);
};

#endif