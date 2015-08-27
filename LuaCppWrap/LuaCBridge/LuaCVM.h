#ifndef __LuaCVM_H_
#define __LuaCVM_H_

#include "lua.hpp"
#include <string>
#include <vector>

class LuaCObjectTranslator;
class LuaCObject;
class LuaCTable;
class LuaCFunction;
class LuaCScriptMgr;

/**
 *@brief ��ʾһ�� Lua �еı��ȼ��� Lua Դ����� ltable.h
 */
class LuaCVM
{
public:
	lua_State* L;
	LuaCScriptMgr* m_pLuaCScriptMgr;

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
	LuaCObject* rawGetObject(int reference, std::string field);
	LuaCObject* getObject(int reference, std::string field);
	LuaCObject* getObject(int reference, LuaCObject* field);
	void setObject(int reference, std::string field, LuaCObject* val);
	void setObject(int reference, LuaCObject* field, LuaCObject* val);
	LuaCFunction* RegisterFunction(std::string fullPath, lua_CFunction function);
};

#endif