#ifndef __LuaCTest_H_
#define __LuaCTest_H_

#include <string>

class LuaCTest
{
protected:
	int m_mem;

public:
	LuaCTest();
	~LuaCTest();

	void setMem(int mem_);
	void sayHello(std::string str);
};

#endif