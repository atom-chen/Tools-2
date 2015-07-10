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
	void slot_tabBarDoubleClicked();            //��Ӧ˫�����صĲۺ���
	void slot_tabDrag(int index, QPoint point);  //��Ӧ�϶������Ĳۺ���
	void slot_closeTab(int);                    //�ر�tab�Ĳۺ���
	void addTestWindow();
};

#endif