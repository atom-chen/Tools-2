#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "AIEditor.h"

class DragDropSys;
class BuildFactory;
class GraphicsScene;
class GraphicsView;

class QtAIEditorSys : public AIEditorSys
{
protected:
	DragDropSys* m_pDragDropSys;				// 拖放数据
	BuildFactory* m_pBuildFactory;				// 工厂生成
	GraphicsScene* m_pGraphicsScene;
	GraphicsView* m_pGraphicsView;

public:
	QtAIEditorSys();
	DragDropSys* getDragDropSysPtr();
	BuildFactory* getBuildFactoryPtr();
	GraphicsScene* getGraphicsScenePtr();
	void setGraphicsScenePtr(GraphicsScene* pGraphicsScene);
	GraphicsView* getGraphicsViewPtr();
	void setGraphicsViewPtr(GraphicsView* pGraphicsView);
};

#define g_pQtAIEditorSys (static_cast<QtAIEditorSys*>(QtAIEditorSys::getSingletonPtr()))
#define g_pDragDropSys g_pQtAIEditorSys->getDragDropSysPtr()
#define g_pBuildFactory g_pQtAIEditorSys->getBuildFactoryPtr()
#define g_pGraphicsScene g_pQtAIEditorSys->getGraphicsScenePtr()
#define g_pGraphicsView g_pQtAIEditorSys->getGraphicsViewPtr()

#endif		// __QTAIEDITORSYS_H_