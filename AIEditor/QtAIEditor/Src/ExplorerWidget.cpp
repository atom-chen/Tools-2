#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// 设置停靠窗口的标题，否则没有标题显示

	// Layout 容器占位窗口
	QWidget* _HLayoutWidget = new QWidget/*(this)*/;	// 构造或者 setWidget 设置窗口
	// this->setWidget(_HLayoutWidget);

	// 设置窗口布局
	m_pHbox = new QHBoxLayout(_HLayoutWidget);	// 构造赋值或者 setLayout 赋值
	//this->setLayout(m_pHbox);
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	m_pModel = new MyBasicFileSystemModel;
	//m_pModel = new MyDirModel;
	m_pModel->setReadOnly(false);
	// m_pModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_pTreeView = new QTreeView(_HLayoutWidget);
	m_pHbox->addWidget(m_pTreeView);
	m_pTreeView->setModel(m_pModel);
	m_pTreeView->setRootIndex(m_pModel->index("E:\\"));

	m_pTreeView->header()->setStretchLastSection(true);
	m_pTreeView->header()->setSortIndicator(0, Qt::AscendingOrder);
	m_pTreeView->header()->setSortIndicatorShown(true);

	QModelIndex index = m_pModel->index(QDir::currentPath());
	m_pTreeView->expand(index);
	m_pTreeView->scrollTo(index);
	m_pTreeView->resizeColumnToContents(0);

	this->setWidget(_HLayoutWidget);	// 最后一定要把 Layout 的父窗口添加到 DockWidget 中，才会刷新一次 Layout ，否则不能刷新
}

ExplorerWidget::~ExplorerWidget()
{

}