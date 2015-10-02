#include "LuaCTestWrap.h"

#ifdef _MSC_VER
#  pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#endif

void main()
{
	LuaCTestWrap_Bind();
}