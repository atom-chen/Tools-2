#ifndef __LuaCTable_H_
#define __LuaCTable_H_

#include "GameEditor.h"
#include "lua.hpp"
#include "LuaCBase.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCVM;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCTable : public LuaCBase
{
public:
	LuaCTable(int reference, LuaCVM* interpreter);
	~LuaCTable();
};

END_NAMESPACE_GAMEEDITOR

#endif