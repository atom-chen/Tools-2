#ifndef __ProgOptions_H
#define __ProgOptions_H

#include <string>

class ProgOptions
{
public:
	std::string m_inFileFullPath;

public:
	void parseParam(int argc, char *argv[]);
};

#endif