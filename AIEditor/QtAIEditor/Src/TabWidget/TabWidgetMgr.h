#ifndef __TabWidgetMgr_H
#define __TabWidgetMgr_H

#include "QtIncAll.h"

class MyTabMainWindow;

class TabWidgetMgr
{
protected:
	MyTabMainWindow* m_pMyTabMainWindow;

public:
	TabWidgetMgr();
	void openTabMainWindow(QWidget* parent = 0);
};

#endif // MAINWINDOW_H