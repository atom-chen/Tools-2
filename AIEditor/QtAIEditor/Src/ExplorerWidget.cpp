#include "ExplorerWidget.h"
#include "MyBasicFileSystemModel.h"
#include "MyDirModel.h"
#include "MyBasicTreeWidget.h"
#include "MyBasicListWidget.h"

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

	// 目录窗口
	m_pTreeWidget = new MyBasicTreeWidget(_HLayoutWidget);
	m_pTreeWidget->add2Layout(m_pHbox);

	// 列表窗口
	m_pListWidget = new MyBasicListWidget;
	//m_pListWidget->resize(400, 200);
	//m_pListWidget->show();
	m_pHbox->addWidget(m_pListWidget);

	this->setWidget(_HLayoutWidget);	// 最后一定要把 Layout 的父窗口添加到 DockWidget 中，才会刷新一次 Layout ，否则不能刷新
}

ExplorerWidget::~ExplorerWidget()
{

}