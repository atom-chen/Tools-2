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
	//此处的n是C++向栈中压入的参数个数，如果和压入栈个数不一致，可能导致栈失衡
	return 0;
}

END_NAMESPACE_GAMEEDITOR