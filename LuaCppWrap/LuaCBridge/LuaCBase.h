#ifndef __LuaCBase_H_
#define __LuaCBase_H_

#include "lua.hpp"
#include <string>

class LuaCVM;
class LuaCObject;

class LuaCBase
{
public:
	bool m_disposed;
	int m_ref;
	LuaCVM* m_luavm;

	std::string m_name;
	int m_count;

public:
	LuaCBase();
	~LuaCBase();

	void PushArgs(LuaCObject* o);
	int getRef();
	void AddRef();
};

#endif