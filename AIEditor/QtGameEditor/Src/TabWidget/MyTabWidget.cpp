#include "MyTabWidget.h"
#include "TabWidgetMgr.h"
#include "QtGameEditorSys.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
	m_tabBar = new MyTabBar;
	setTabBar(m_tabBar);     //这里是关键，这样用我们自定义的CTabBar替换原来的QTabBar

	this->setMovable(true);
	this->setTabsClosable(true);
	this->setTabShape(QTabWidget::Triangular);

	QObject::connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));
}

void MyTabWidget::onTabCloseRequested(int index)
{
	if (this->count() == 1)		// 如果只剩下最后一个
	{
		g_pTabWidgetMgr->hideMainWindow();
	}
}