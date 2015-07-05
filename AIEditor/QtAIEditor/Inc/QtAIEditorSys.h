#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "AIEditor.h"

class DragDropSys;
class BuildFactory;

class QtAIEditorSys : public AIEditorSys
{
public:
	DragDropSys* m_pDragDropSys;				// 拖放数据
	BuildFactory* m_pBuildFactory;				// 工厂生成

public:
	QtAIEditorSys();

	// 这里写是为了解决没有实例化模板的时候导致的链接错误
//protected:
//	static QtAIEditorSys* m_sSingleton;
//
//public:
//	static QtAIEditorSys* getSingletonPtr();
};

#define g_pQtAIEditorSys ((QtAIEditorSys*)(QtAIEditorSys::getSingletonPtr()))

#endif		// __QTAIEDITORSYS_H_