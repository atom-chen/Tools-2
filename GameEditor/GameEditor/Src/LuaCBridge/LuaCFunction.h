#ifndef __LuaCFunction_H_
#define __LuaCFunction_H_

#include "GameEditor.h"
#include "lua.hpp"
#include "LuaCBase.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;

/**
 *@brief 表示一个 Lua 中的表，等价于 Lua 源代码的 ltable.h
 */
class GAMEEDITOR_EXPORT LuaCFunction : public LuaCBase
{
public:
	LuaCFunction(int reference, LuaCVM* interpreter);
	~LuaCFunction();
};

END_NAMESPACE_GAMEEDITOR

#endif