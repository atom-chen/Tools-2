#ifndef __QTAIEDITORSYS_H_
#define __QTAIEDITORSYS_H_

#include "AIEditor.h"

#include "IDragDropSys.h"
#include "IBuildFactory.h"

class QtAIEditorSys : public AIEditorSys
{
public:
	IDragDropSys* m_pDragDropSys;				// �Ϸ�����
	IBuildFactory* m_pBuildFactory;				// ��������

public:
	QtAIEditorSys();

	// ����д��Ϊ�˽�����Ӵ���
protected:
	static QtAIEditorSys* m_sSingleton;

public:
	static QtAIEditorSys* getSingletonPtr();
};

#endif		// __QTAIEDITORSYS_H_