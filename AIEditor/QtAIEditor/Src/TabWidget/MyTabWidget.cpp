#include "MyTabWidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
	m_tabBar = new MyTabBar;
	setTabBar(m_tabBar);     //�����ǹؼ��������������Զ����CTabBar�滻ԭ����QTabBar
}