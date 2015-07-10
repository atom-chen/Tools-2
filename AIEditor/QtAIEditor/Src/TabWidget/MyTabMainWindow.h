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
	void slot_tabBarDoubleClicked();            //��Ӧ˫�����صĲۺ���
	void slot_tabDrag(int index, QPoint point);  //��Ӧ�϶������Ĳۺ���
	void slot_closeTab(int);                    //�ر�tab�Ĳۺ���
};

#endif // MAINWINDOW_H