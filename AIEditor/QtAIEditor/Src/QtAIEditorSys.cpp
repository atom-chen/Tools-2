#include "QtAIEditorSys.h"
#include "DragDropSys.h"
#include "BuildFactory.h"
#include "GraphicsScene.h"

QtAIEditorSys::QtAIEditorSys()
{
	m_pDragDropSys = new DragDropSys();
	m_pBuildFactory = new BuildFactory();
}

DragDropSys* QtAIEditorSys::getDragDropSysPtr()
{
	return m_pDragDropSys;
}

BuildFactory* QtAIEditorSys::getBuildFactoryPtr()
{
	return m_pBuildFactory;
}

GraphicsScene* QtAIEditorSys::getGraphicsScenePtr()
{
	return m_pGraphicsScene;
}

void QtAIEditorSys::setGraphicsScenePtr(GraphicsScene* pGraphicsScene)
{
	m_pGraphicsScene = pGraphicsScene;
}