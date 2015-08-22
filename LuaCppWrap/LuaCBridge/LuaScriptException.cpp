#include "LuaScriptException.h"

BEGIN_NAMESPACE_GAMEEDITOR

LuaScriptException::LuaScriptException()
{

}

LuaScriptException::~LuaScriptException()
{

}

LuaScriptException::LuaScriptException(std::string message, std::string source) : std::exception()
{
	this->source = source;
}

LuaScriptException::LuaScriptException(std::exception innerException, std::string source)
	: std::exception()
{
	this->source = source;
}

bool LuaScriptException::getIsNetException()
{
	return isNet;
}

bool LuaScriptException::setIsNetException(bool isNet_)
{
	return isNet;
}

std::string LuaScriptException::getSource()
{
	return source;
}

END_NAMESPACE_GAMEEDITOR