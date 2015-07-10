#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"
#include "MyBasicMVCTreeWidget.h"
#include "MyBasicListWidget.h"
#include "MyBasicTreeView.h"
#include "QtAIEditorSys.h"
#include "TabWidgetMgr.h"
#include "MyBasicListWidgetItemData.h"
#include "MyBasicListWidgetItem.h"

ExplorerWidget::ExplorerWidget(QWidget *parent)
	: QDockWidget(parent, 0)
{
	this->setObjectName(QStringLiteral("ExplorerWidget"));
	this->setWindowTitle(QStringLiteral("ExplorerWidget"));		// 设置停靠窗口的标题，否则没有标题显示

	// Layout 容器占位窗口
	QWidget* _HLayoutWidget = new QWidget/*(this)*/;	// 构造或者 setWidget 设置窗口

	// 设置窗口布局
	m_pHbox = new QHBoxLayout/*(_HLayoutWidget)*/;	// 构造赋值或者 setLayout 赋值
	m_pHbox->setObjectName(QStringLiteral("ExplorerWidgetHbox"));
	m_pHbox->setContentsMargins(0, 0, 0, 0);

	// 目录窗口
	m_pTreeWidget = new MyBasicMVCTreeWidget(_HLayoutWidget);
	m_pTreeWidget->add2Layout(m_pHbox);
	// 添加事件监听器
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(clicked(const QModelIndex)), this, SLOT(onTreeViewClick(const QModelIndex)));
	QObject::connect(m_pTreeWidget->getTreeViewPtr(), SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onTreeViewDoubleClick(const QModelIndex)));

	// 列表窗口
	m_pListWidget = new MyBasicListWidget;
	//m_pListWidget->resize(400, 200);
	//m_pListWidget->show();
	m_pHbox->addWidget(m_pListWidget);
	// 添加监听事件
	QObject::connect(m_pListWidget->getListWidgetPtr(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListDoubleClick(QListWidgetItem *)));

	_HLayoutWidget->setLayout(m_pHbox);
	this->setWidget(_HLayoutWidget);	// 最后一定要把 Layout 的父窗口添加到 DockWidget 中，才会刷新一次 Layout ，否则不能刷新
}

ExplorerWidget::~ExplorerWidget()
{

}

// 点击左边资源管理器树
void ExplorerWidget::onTreeViewClick(const QModelIndex & index)
{
	QFileInfo fileInfo = m_pTreeWidget->fileInfo(index);
	m_pListWidget->updateListWidget(fileInfo.absoluteFilePath());
}

void ExplorerWidget::onTreeViewDoubleClick(const QModelIndex & index)
{
	// QAbstractItemModel* m = (QAbstractItemModel*)index.model();
	QFileInfo fileInfo = m_pTreeWidget->fileInfo(index);
}

// 双击 List 项
void ExplorerWidget::onListDoubleClick(QListWidgetItem *Item)
{
	// test
	//MyBasicListWidgetItemData itemData;
	//QVariant userData = Item->data(Qt::UserRole);
	//if (userData.canConvert<MyBasicListWidgetItemData>())
	//{
	//	itemData = userData.value<MyBasicListWidgetItemData>();
	//}
	MyBasicListWidgetItem* pItem = (MyBasicListWidgetItem*)Item;
	MyBasicListWidgetItemData* pItemData = pItem->getItemData();
	if (pItemData->getBFile())	// 只有是文件的时候才会编辑
	{
		g_pTabWidgetMgr->openOneActionEffectEditor(pItemData->getFullPath());
	}
}