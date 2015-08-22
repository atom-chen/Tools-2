#ifndef __LuaScriptException_H_
#define __LuaScriptException_H_

#include "lua.hpp"
#include <string>
#include <Exception>

class LuaScriptException : public std::exception
{
public:
	bool isNet;
private:
	std::string source;

public:
	LuaScriptException();
	LuaScriptException(std::string message, std::string source);
	LuaScriptException(std::exception innerException, std::string source);
	~LuaScriptException();

	bool getIsNetException();
	bool setIsNetException(bool isNet_);
	std::string getSource();
};

#endif