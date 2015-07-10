#include "MyTabWidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
	m_tabBar = new MyTabBar;
	setTabBar(m_tabBar);     //这里是关键，这样用我们自定义的CTabBar替换原来的QTabBar
}