#include "MyBasicMVCTreeWidget.h"
#include "MyBasicTreeView.h"
#include "MyBasicFileSystemModel.h"

MyBasicMVCTreeWidget::MyBasicMVCTreeWidget(QWidget *parent)
{
	m_pModel = new MyBasicFileSystemModel;
	m_pTreeView = new MyBasicTreeView(parent);
	m_pTreeView->setModel(m_pModel);
	m_pTreeView->setRootIndex(m_pModel->index("E:/Self"));
	// ����� QFileSystemModel �����û���������δ��룬�ǲ��ܿ����κ����ݵġ����� QDirModel û������Ĵ���Ҳ���Կ�������
	{
		QModelIndex index = m_pModel->index(QDir::currentPath());
		m_pTreeView->scrollTo(index);
	}
}

MyBasicTreeView* MyBasicMVCTreeWidget::getTreeViewPtr()
{
	return m_pTreeView;
}

void MyBasicMVCTreeWidget::add2Layout(QHBoxLayout* layout)
{
	layout->addWidget(m_pTreeView);
}

void MyBasicMVCTreeWidget::add2Splitter(QSplitter * splitter)
{
	splitter->addWidget(m_pTreeView);
}

QModelIndex MyBasicMVCTreeWidget::currentIndex() const
{
	return m_pTreeView->currentIndex();
}

QFileInfo MyBasicMVCTreeWidget::fileInfo(const QModelIndex &index) const
{
	QFileInfo fileInfo = m_pModel->fileInfo(index);
	return fileInfo;
}