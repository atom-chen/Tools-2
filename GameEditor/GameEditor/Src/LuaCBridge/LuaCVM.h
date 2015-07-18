#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include <vector>
#include "LuaCObject.h"

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCObjectTranslator;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCVM
{
public:
	lua_State* m_L;

protected:
	LuaCObjectTranslator* m_translator;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// ���� Lua �����
	void closeLua();				// �ر� Lua �����

	LuaCObject getLuaObject(std::string fullPath);
	void setLuaObject(std::string fullPath);
	LuaCObject getObject(std::vector<std::string>& remainingPath);
	void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
};

END_NAMESPACE_GAMEEDITOR

#endif