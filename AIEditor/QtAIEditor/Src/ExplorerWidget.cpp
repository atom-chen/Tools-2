#include "ExplorerWidget.h"
#include "FileSystemModel.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// 设置停靠窗口的标题，否则没有标题显示
	// 设置窗口布局
	m_pHbox = new QHBoxLayout;
	this->setLayout(m_pHbox);

	m_pModel = new FileSystemModel;
	m_pModel->setReadOnly(false);
	//m_pModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

	m_pTreeView = new QTreeView;
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
}

ExplorerWidget::~ExplorerWidget()
{

}