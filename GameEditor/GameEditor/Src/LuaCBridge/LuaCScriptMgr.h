#ifndef __LuaScriptMgr_H_
#define __LuaScriptMgr_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaCScriptMgr
{
protected:
	lua_State* m_L;

public:
	LuaCScriptMgr();
	~LuaCScriptMgr();

	void openLua();					// ���� Lua �����
	void closeLua();				// �ر� Lua �����
	void setLuaFilePath(std::string path);	// ���� Lua �ļ��Ĳ���Ŀ¼
	void setCFilePath(std::string path);	// ���� C ��Ĳ���Ŀ¼
};

END_NAMESPACE_GAMEEDITOR

#endif