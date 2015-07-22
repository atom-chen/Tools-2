#ifndef __LuaScriptException_H_
#define __LuaScriptException_H_

#include "GameEditor.h"
#include "lua.hpp"
#include <string>
#include <Exception>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT LuaScriptException : public std::exception
{
public:
	bool isNet;
private:
#include "PushWarn.h"
	std::string source;
#include "PopWarn.h"

public:
	LuaScriptException();
	LuaScriptException(std::string message, std::string source);
	LuaScriptException(std::exception innerException, std::string source);
	~LuaScriptException();

	bool getIsNetException();
	bool setIsNetException(bool isNet_);
	std::string getSource();
};

END_NAMESPACE_GAMEEDITOR

#endif