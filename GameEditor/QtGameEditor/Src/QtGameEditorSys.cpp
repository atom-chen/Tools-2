#include "QtGameEditorSys.h"
#include "DragDropSys.h"
#include "BuildFactory.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
#include "TabWidgetMgr.h"

QtGameEditorSys::QtGameEditorSys()
{
	m_pDragDropSys = new DragDropSys();
	m_pBuildFactory = new BuildFactory();
	m_pTabWidgetMgr = new TabWidgetMgr;
}

DragDropSys* QtGameEditorSys::getDragDropSysPtr()
{
	return m_pDragDropSys;
}

BuildFactory* QtGameEditorSys::getBuildFactoryPtr()
{
	return m_pBuildFactory;
}

MyGraphicsScene* QtGameEditorSys::getGraphicsScenePtr()
{
	return m_pGraphicsScene;
}

void QtGameEditorSys::setGraphicsScenePtr(MyGraphicsScene* pGraphicsScene)
{
	m_pGraphicsScene = pGraphicsScene;
}

MyGraphicsView* QtGameEditorSys::getGraphicsViewPtr()
{
	return  m_pGraphicsView;
}

void QtGameEditorSys::setGraphicsViewPtr(MyGraphicsView* pGraphicsView)
{
	m_pGraphicsView = pGraphicsView;
}

TabWidgetMgr* QtGameEditorSys::getTabWidgetMgrPtr()
{
	return m_pTabWidgetMgr;
}