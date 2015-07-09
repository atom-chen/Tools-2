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
	QTreeView::setRootIndex(index);	// ����� QFileSystemModel ģ�ͣ����� QTreeView::setRootIndex û��Ч������Ҫ��ͬʱ���� QFileSystemModel::setRootPath �� QTreeView::setRootIndex ���С� QDirModel ֻ��Ҫ���� QTreeView::setRootIndex �����ˡ�
}

void MyBasicTreeView::scrollTo(const QModelIndex &index, ScrollHint hint)
{
	this->expand(index);
	QTreeView::scrollTo(index);
	this->resizeColumnToContents(0);
}

void MyBasicTreeView::setItemsExpandable(bool enable)
{
	QTreeView::setItemsExpandable(false);		// �����Ƿ������չ
}