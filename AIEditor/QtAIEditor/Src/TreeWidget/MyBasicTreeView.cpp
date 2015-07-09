#include "MyBasicTreeView.h"  

MyBasicTreeView::MyBasicTreeView(QWidget *parent)
{
	this->header()->setStretchLastSection(true);
	this->header()->setSortIndicator(0, Qt::AscendingOrder);
	this->header()->setSortIndicatorShown(true);
}

void MyBasicTreeView::setModel(QAbstractItemModel *model)
{
	QTreeView::setModel(model);
}

void MyBasicTreeView::setRootIndex(const QModelIndex &index)
{
	QTreeView::setRootIndex(index);	// 如果是 QFileSystemModel 模型，调用 QTreeView::setRootIndex 没有效果，需要释同时调用 QFileSystemModel::setRootPath 和 QTreeView::setRootIndex 才行。 QDirModel 只需要调用 QTreeView::setRootIndex 就行了。
}

void MyBasicTreeView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
	this->expand(index);
	QTreeView::scrollTo(index);
	this->resizeColumnToContents(0);
}

void MyBasicTreeView::setItemsExpandable(bool enable)
{
	QTreeView::setItemsExpandable(false);		// 设置是否可以扩展
}