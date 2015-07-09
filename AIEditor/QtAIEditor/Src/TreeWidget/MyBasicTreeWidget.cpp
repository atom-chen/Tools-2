#include "MyBasicTreeWidget.h"
#include "MyBasicTreeView.h"
#include "MyBasicFileSystemModel.h"

MyBasicTreeWidget::MyBasicTreeWidget(QWidget *parent)
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

MyBasicTreeView* MyBasicTreeWidget::getTreeViewPtr()
{
	return m_pTreeView;
}

void MyBasicTreeWidget::add2Layout(QHBoxLayout* layout)
{
	layout->addWidget(m_pTreeView);
}