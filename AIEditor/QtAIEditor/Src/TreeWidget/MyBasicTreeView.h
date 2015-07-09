#ifndef __MyBasicTreeView_H
#define __MyBasicTreeView_H

#include "QtIncAll.h"

class MyBasicTreeView : public QTreeView
{
	Q_OBJECT

public:
	MyBasicTreeView(QWidget *parent = 0);
	void setModel(QAbstractItemModel *model);
	void setItemsExpandable(bool enable);
	void setRootIndex(const QModelIndex &index);
	void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
};

#endif