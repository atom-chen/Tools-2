#include "QtAIEditorSys.h"
#include "DragDropSys.h"
#include "BuildFactory.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
#include "TabWidgetMgr.h"

QtAIEditorSys::QtAIEditorSys()
{
	m_pDragDropSys = new DragDropSys();
	m_pBuildFactory = new BuildFactory();
	m_pTabWidgetMgr = new TabWidgetMgr;
}

DragDropSys* QtAIEditorSys::getDragDropSysPtr()
{
	return m_pDragDropSys;
}

BuildFactory* QtAIEditorSys::getBuildFactoryPtr()
{
	return m_pBuildFactory;
}

MyGraphicsScene* QtAIEditorSys::getGraphicsScenePtr()
{
	return m_pGraphicsScene;
}

void QtAIEditorSys::setGraphicsScenePtr(MyGraphicsScene* pGraphicsScene)
{
	m_pGraphicsScene = pGraphicsScene;
}

MyGraphicsView* QtAIEditorSys::getGraphicsViewPtr()
{
	return  m_pGraphicsView;
}

void QtAIEditorSys::setGraphicsViewPtr(MyGraphicsView* pGraphicsView)
{
	m_pGraphicsView = pGraphicsView;
}

TabWidgetMgr* QtAIEditorSys::getTabWidgetMgrPtr()
{
	return m_pTabWidgetMgr;
}