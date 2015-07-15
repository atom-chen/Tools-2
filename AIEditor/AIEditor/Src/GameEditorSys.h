#ifndef __AIEDITORSYS_H_
#define __AIEDITORSYS_H_

#include "GameEditor.h"

BEGIN_NAMESPACE_GAMEEDITOR

class AIEDITOR_EXPORT GameEditorSys : public Singleton<GameEditorSys>
{
public:
	GameEditorSys();

private:
	// ��Ҫ�ֹ���������������������������Ϊ�˵� AIEditor ģ��û��ʹ�� g_pGameEditorSys ��ʱ�򣬵���ģ���� Singleton ������ DLL �е��������⡣��� AIEditor ģ��ʹ�� g_pGameEditorSys������ȥ�����������
	void instanceT();
};

#define g_pGameEditorSys GameEditorSys::getSingletonPtr()

END_NAMESPACE_GAMEEDITOR

#endif		// __AIEDITORSYS_H_