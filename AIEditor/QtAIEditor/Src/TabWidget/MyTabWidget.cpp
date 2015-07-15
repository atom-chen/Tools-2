#include "MyTabWidget.h"
#include "TabWidgetMgr.h"
#include "QtGameEditorSys.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
	m_tabBar = new MyTabBar;
	setTabBar(m_tabBar);     //�����ǹؼ��������������Զ����CTabBar�滻ԭ����QTabBar

	this->setMovable(true);
	this->setTabsClosable(true);
	this->setTabShape(QTabWidget::Triangular);

	QObject::connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));
}

void MyTabWidget::onTabCloseRequested(int index)
{
	if (this->count() == 1)		// ���ֻʣ�����һ��
	{
		g_pTabWidgetMgr->hideMainWindow();
	}
}