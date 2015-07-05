#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "AIEditor.h"

class DragDropSys;
class BuildFactory;

class QtAIEditorSys : public AIEditorSys
{
public:
	DragDropSys* m_pDragDropSys;				// �Ϸ�����
	BuildFactory* m_pBuildFactory;				// ��������

public:
	QtAIEditorSys();

	// ����д��Ϊ�˽��û��ʵ����ģ���ʱ���µ����Ӵ���
//protected:
//	static QtAIEditorSys* m_sSingleton;
//
//public:
//	static QtAIEditorSys* getSingletonPtr();
};

#define g_pQtAIEditorSys ((QtAIEditorSys*)(QtAIEditorSys::getSingletonPtr()))

#endif		// __QTAIEDITORSYS_H_