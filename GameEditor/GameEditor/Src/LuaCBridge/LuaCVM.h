#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "GameEditor.h"
#include "lua.hpp"

BEGIN_NAMESPACE_GAMEEDITOR

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCVM
{
public:
	lua_State* m_L;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// ���� Lua �����
	void closeLua();				// �ر� Lua �����
};

END_NAMESPACE_GAMEEDITOR

#endif