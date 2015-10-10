#ifndef __LuaCUtil_H_
#define __LuaCUtil_H_

#include <string>
#include <vector>

class LuaCUtil
{
public:
	static void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
};

#endif