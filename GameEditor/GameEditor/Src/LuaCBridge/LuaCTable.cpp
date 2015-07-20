#include "LuaCTable.h"
#include "LuaCVM.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaCTable::LuaCTable(int reference, LuaCVM* interpreter)
{
	_Reference = reference;
	_Interpreter = interpreter;
	translator = interpreter->translator;
}

LuaCTable::~LuaCTable()
{

}

END_NAMESPACE_GAMEEDITOR