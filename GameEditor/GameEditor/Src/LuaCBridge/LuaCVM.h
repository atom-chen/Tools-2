#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include <vector>

BEGIN_NAMESPACE_GAMEEDITOR

class LuaCObjectTranslator;
class LuaCObject;
class LuaCTable;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class GAMEEDITOR_EXPORT LuaCVM
{
public:
	lua_State* L;

public:
	LuaCObjectTranslator* translator;

public:
	LuaCVM();
	~LuaCVM();

	void openLua();					// ���� Lua �����
	void closeLua();				// �ر� Lua �����

	void doString(std::string value);
	void doFile(std::string path);
	LuaCObject* getLuaObject(std::string fullPath);
	void setLuaObject(std::string fullPath, LuaCObject* value);
	LuaCObject* getObject(std::vector<std::string>& remainingPath);
	void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
	void setObject(std::vector<std::string>& remainingPath, LuaCObject* value);

	void NewTable(std::string fullPath);
	LuaCTable* NewTable();
};

END_NAMESPACE_GAMEEDITOR

#endif