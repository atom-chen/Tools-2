#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "AIEditor.h"

class DragDropSys;
class BuildFactory;
class MyGraphicsScene;
class MyGraphicsView;
class TabWidgetMgr;

class QtAIEditorSys : public AIEditorSys
{
protected:
	DragDropSys* m_pDragDropSys;				// 拖放数据
	BuildFactory* m_pBuildFactory;				// 工厂生成
	MyGraphicsScene* m_pGraphicsScene;
	MyGraphicsView* m_pGraphicsView;
	TabWidgetMgr* m_pTabWidgetMgr;

public:
	QtAIEditorSys();
	DragDropSys* getDragDropSysPtr();
	BuildFactory* getBuildFactoryPtr();
	MyGraphicsScene* getGraphicsScenePtr();
	void setGraphicsScenePtr(MyGraphicsScene* pGraphicsScene);
	MyGraphicsView* getGraphicsViewPtr();
	void setGraphicsViewPtr(MyGraphicsView* pGraphicsView);
	TabWidgetMgr* getTabWidgetMgrPtr();
};

#define g_pQtAIEditorSys (static_cast<QtAIEditorSys*>(QtAIEditorSys::getSingletonPtr()))
#define g_pDragDropSys g_pQtAIEditorSys->getDragDropSysPtr()
#define g_pBuildFactory g_pQtAIEditorSys->getBuildFactoryPtr()
#define g_pGraphicsScene g_pQtAIEditorSys->getGraphicsScenePtr()
#define g_pGraphicsView g_pQtAIEditorSys->getGraphicsViewPtr()
#define g_pTabWidgetMgr g_pQtAIEditorSys->getTabWidgetMgrPtr()

#endif		// __QTAIEDITORSYS_H_