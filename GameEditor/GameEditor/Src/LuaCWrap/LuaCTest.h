#ifndef __LuaCTest_H_
#define __LuaCTest_H_

#include "GameEditor.h"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaCTest
{
public:
	LuaCTest();
	~LuaCTest();

	void sayHello(std::string str);
};

END_NAMESPACE_GAMEEDITOR

#endif