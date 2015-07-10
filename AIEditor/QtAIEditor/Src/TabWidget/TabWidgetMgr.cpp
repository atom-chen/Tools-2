#include "TabWidgetMgr.h"
#include "MyTabMainWindow.h"

TabWidgetMgr::TabWidgetMgr()
{
	m_pMyTabMainWindow = nullptr;
}

void TabWidgetMgr::openTabMainWindow(QWidget* parent)
{
	if (m_pMyTabMainWindow == nullptr)
	{
		m_pMyTabMainWindow = new MyTabMainWindow;
	}

	m_pMyTabMainWindow->show();
}

void TabWidgetMgr::openOneActionEffectEditor(std::string path)
{
	openTabMainWindow(nullptr);
	m_pMyTabMainWindow->openOneActionEffectEditor(path);
}