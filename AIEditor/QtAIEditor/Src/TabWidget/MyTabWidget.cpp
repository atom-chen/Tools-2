#include "MyTabWidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :QTabWidget(parent)
{
	tabBar = new MyTabBar;
	setTabBar(tabBar);     //�����ǹؼ��������������Զ����CTabBar�滻ԭ����QTabBar
}
