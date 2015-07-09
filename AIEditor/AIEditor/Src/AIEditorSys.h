#ifndef __AIEDITORSYS_H_
#define __AIEDITORSYS_H_

#include "AIEditor.h"

BEGIN_NAMESPACE_AIEDITOR

class AIEDITOR_EXPORT AIEditorSys : public Singleton<AIEditorSys>
{
public:
	AIEditorSys();

private:
	// ��Ҫ�ֹ���������������������������Ϊ�˵� AIEditor ģ��û��ʹ�� g_pAIEditorSys ��ʱ�򣬵���ģ���� Singleton ������ DLL �е��������⡣��� AIEditor ģ��ʹ�� g_pAIEditorSys������ȥ�����������
	void instanceT();
};

#define g_pAIEditorSys AIEditorSys::getSingletonPtr()

END_NAMESPACE_AIEDITOR

#endif		// __AIEDITORSYS_H_