#include "MyBasicTreeWidget.h"
#include "MyBasicTreeView.h"
#include "MyBasicFileSystemModel.h"

MyBasicTreeWidget::MyBasicTreeWidget(QWidget *parent)
{
	m_pModel = new MyBasicFileSystemModel;
	m_pTreeView = new MyBasicTreeView(parent);
	m_pTreeView->setModel(m_pModel);
	m_pTreeView->setRootIndex(m_pModel->index("E:/Self"));
	// 如果是 QFileSystemModel ，如果没有下面的这段代码，是不能看到任何内容的。但是 QDirModel 没有下面的代码也可以看到内容
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