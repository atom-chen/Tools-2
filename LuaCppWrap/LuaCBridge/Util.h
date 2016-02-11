#ifndef __Util_H_
#define __Util_H_

#include <string>
#include <vector>

class Util
{
public:
	static void split(std::string& s, std::string& delim, std::vector<std::string>* ret);
};

#endif