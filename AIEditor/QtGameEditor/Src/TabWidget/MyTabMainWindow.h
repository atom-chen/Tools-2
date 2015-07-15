#ifndef __MyTabMainWindow_H
#define __MyTabMainWindow_H

#include <string>
#include <vector>
#include "QtIncAll.h"
#include "MyTabWidget.h"
#include "MyTabBar.h"

class MyTabSubWidgetBase;

class MyTabMainWindow :public QMainWindow
{
	Q_OBJECT

private:
	typedef std::vector<MyTabSubWidgetBase*>::iterator TabSubWidgetIte;
	std::vector<MyTabSubWidgetBase*> m_frameVec;

public:
	MyTabMainWindow(QWidget* = 0);
	void openOneActionEffectEditor(std::string path);
	void removeOneEditor(std::string path);

private:
	MyTabWidget *m_pTabWidget;
	private slots:
	void slot_tabBarDoubleClicked();            //响应双击弹回的槽函数
	void slot_tabDrag(int index, QPoint point);  //响应拖动动作的槽函数
	void slot_closeTab(int);                    //关闭tab的槽函数
	void addTestWindow();
};

#endif