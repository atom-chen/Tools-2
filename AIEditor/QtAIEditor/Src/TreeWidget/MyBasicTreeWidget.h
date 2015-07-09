#ifndef __MyBasicTreeWidget_H
#define __MyBasicTreeWidget_H

#include "QtIncAll.h"

class MyBasicTreeView;
class MyBasicFileSystemModel;

class MyBasicTreeWidget
{
protected:
	MyBasicTreeView* m_pTreeView;
	MyBasicFileSystemModel* m_pModel;

public:
	MyBasicTreeWidget(QWidget *parent = 0);
	MyBasicTreeView* getTreeViewPtr();
	void add2Layout(QHBoxLayout* layout);
};

#endif