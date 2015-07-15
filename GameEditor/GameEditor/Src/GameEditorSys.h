#ifndef __AIEDITORSYS_H_
#define __AIEDITORSYS_H_

#include "GameEditor.h"

BEGIN_NAMESPACE_GAMEEDITOR

class SkillActionNodeConfig;

class GAMEEDITOR_EXPORT GameEditorSys : public Singleton<GameEditorSys>
{
protected:
	SkillActionNodeConfig* m_pSkillActionNodeConfig;

public:
	GameEditorSys();
	SkillActionNodeConfig* getSkillActionNodeConfigPtr();

private:
	// ��Ҫ�ֹ���������������������������Ϊ�˵� AIEditor ģ��û��ʹ�� g_pGameEditorSys ��ʱ�򣬵���ģ���� Singleton ������ DLL �е��������⡣��� AIEditor ģ��ʹ�� g_pGameEditorSys������ȥ�����������
	void instanceT();
};

#define g_pGameEditorSys GameEditorSys::getSingletonPtr()
#define g_pSkillActionNodeConfig g_pGameEditorSys->getSkillActionNodeConfigPtr()

END_NAMESPACE_GAMEEDITOR

#endif		// __AIEDITORSYS_H_