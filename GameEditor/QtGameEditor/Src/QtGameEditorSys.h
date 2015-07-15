#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "GameEditor.h"

class DragDropSys;
class BuildFactory;
class MyGraphicsScene;
class MyGraphicsView;
class TabWidgetMgr;

class QtGameEditorSys : public GameEditorSys
{
protected:
	DragDropSys* m_pDragDropSys;				// 拖放数据
	BuildFactory* m_pBuildFactory;				// 工厂生成
	MyGraphicsScene* m_pGraphicsScene;
	MyGraphicsView* m_pGraphicsView;
	TabWidgetMgr* m_pTabWidgetMgr;

public:
	QtGameEditorSys();
	DragDropSys* getDragDropSysPtr();
	BuildFactory* getBuildFactoryPtr();
	MyGraphicsScene* getGraphicsScenePtr();
	void setGraphicsScenePtr(MyGraphicsScene* pGraphicsScene);
	MyGraphicsView* getGraphicsViewPtr();
	void setGraphicsViewPtr(MyGraphicsView* pGraphicsView);
	TabWidgetMgr* getTabWidgetMgrPtr();

	virtual void init();
};

#define g_pQtGameEditorSys (static_cast<QtGameEditorSys*>(QtGameEditorSys::getSingletonPtr()))
#define g_pDragDropSys g_pQtGameEditorSys->getDragDropSysPtr()
#define g_pBuildFactory g_pQtGameEditorSys->getBuildFactoryPtr()
#define g_pGraphicsScene g_pQtGameEditorSys->getGraphicsScenePtr()
#define g_pGraphicsView g_pQtGameEditorSys->getGraphicsViewPtr()
#define g_pTabWidgetMgr g_pQtGameEditorSys->getTabWidgetMgrPtr()

#endif		// __QTAIEDITORSYS_H_