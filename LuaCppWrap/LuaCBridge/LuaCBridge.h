#ifndef __LuaCBridge_H_
#define __LuaCBridge_H_

#include "lua.hpp"
#include <string>

/**
 *@brief 表示一个 Lua 中的模块，一个表中的数据，加上操作表中的功能
 */
class LuaCBridge
{
	std::string m_bridgeName;		// 就是 Lua 和 C 之间的表名字

public:
	LuaCBridge();
	~LuaCBridge();

	void callFunction(const char* funcName_);
	void callGlobalFunction(const char* funcName_);
	void getFunction(const char* funcName_);
	void getGlobalFunction(const char* funcName_);
	void getData(const char* dataName_);
	void getGlobalData(const char* dataName_);
};

#endif