#ifndef __MyTabWidget_H
#define __MyTabWidget_H

#include <QTabWidget>
#include <QtGui>
#include "MyTabBar.h"

class MyTabWidget :public QTabWidget
{
	Q_OBJECT
public:
	MyTabWidget(QWidget* = 0);
	virtual ~MyTabWidget(){};
public:
	MyTabBar *m_tabBar;
};

#endif