#include "LuaCTestWrap.h"
#include "GameEditorSys.h"
#include "LuaCScriptMgr.h"

BEGIN_NAMESPACE_GAMEEDITOR

void LuaCTestWrap_Bind()
{

}

int LuaCTestWrap_sayHello(lua_State* L)
{
	LuaCScriptMgr::CheckArgsCount(L, 1);
	const char* pParam = lua_tostring(L, -1);
	//�˴���n��C++��ջ��ѹ��Ĳ��������������ѹ��ջ������һ�£����ܵ���ջʧ��
	return 0;
}

END_NAMESPACE_GAMEEDITOR