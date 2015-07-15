#ifndef __MyTabWidget_H
#define __MyTabWidget_H

#include <QTabWidget>
#include <QtGui>
#include "MyTabBar.h"

class MyTabWidget :public QTabWidget
{
	Q_OBJECT

public:
	MyTabBar *m_tabBar;

public:
	MyTabWidget(QWidget* = 0);
	virtual ~MyTabWidget(){};

public Q_SLOTS:
	void onTabCloseRequested(int index);		// 关闭一个 Tab 标签
};

#endif