#ifndef __LuaCFunction_H_
#define __LuaCFunction_H_

#include "GameEditor.h"
#include "lua.hpp"
#include "LuaCBase.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCFunction : public LuaCBase
{
public:
	LuaCFunction(int reference, LuaCVM* interpreter);
	~LuaCFunction();
};

END_NAMESPACE_GAMEEDITOR

#endif