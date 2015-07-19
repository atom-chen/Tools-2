#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include <vector>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCObjectTranslator;
class LuaCObject;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCVM
{
public:
	lua_State* L;

protected:
	LuaCObjectTranslator* translator;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// 创建 Lua 虚拟机
	void closeLua();				// 关闭 Lua 虚拟机

	LuaCObject* getLuaObject(std::string fullPath);
	void setLuaObject(std::string fullPath, LuaCObject* value);
	LuaCObject* getObject(std::vector<std::string>& remainingPath);
	void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
	void setObject(std::vector<std::string>& remainingPath, LuaCObject* value);
};

END_NAMESPACE_GAMEEDITOR

#endif