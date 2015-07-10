#ifndef __MyTabMainWindow_H
#define __MyTabMainWindow_H

#include "QtIncAll.h"
#include "MyTabWidget.h"
#include "MyTabBar.h"

class MyTabMainWindow :public QMainWindow
{
	Q_OBJECT
public:
	MyTabMainWindow(QWidget* = 0);
private:
	MyTabWidget *tabWidget;
	private slots:
	void slot_tabBarDoubleClicked();            //响应双击弹回的槽函数
	void slot_tabDrag(int index, QPoint point);  //响应拖动动作的槽函数
	void slot_closeTab(int);                    //关闭tab的槽函数
};

#endif // MAINWINDOW_H