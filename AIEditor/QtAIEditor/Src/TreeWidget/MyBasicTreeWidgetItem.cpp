#include "MyBasicTreeWidgetItem.h"

MyBasicTreeWidgetItem::MyBasicTreeWidgetItem(QTreeWidget *view, const QStringList &strings, int type)
	: QTreeWidgetItem(view, strings, type)
{
	
}

MyBasicTreeWidgetItem::MyBasicTreeWidgetItem(QTreeWidgetItem *parent, const QStringList &strings, int type)
	: QTreeWidgetItem(parent, strings, type)
{

}