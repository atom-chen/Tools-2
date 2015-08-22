#ifndef __LuaCTest_H_
#define __LuaCTest_H_

#include "GameEditor.h"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaCTest
{
protected:
	int m_mem;

public:
	LuaCTest();
	~LuaCTest();

	void setMem(int mem_);
	void sayHello(std::string str);
};

END_NAMESPACE_GAMEEDITOR

#endif