#ifndef __TabWidgetMgr_H
#define __TabWidgetMgr_H

#include "QtIncAll.h"
#include <string>

class MyTabMainWindow;

class TabWidgetMgr
{
protected:
	MyTabMainWindow* m_pMyTabMainWindow;

public:
	TabWidgetMgr();
	void openTabMainWindow(QWidget* parent = 0);
	void openOneActionEffectEditor(std::string path);
};

#endif // MAINWINDOW_H