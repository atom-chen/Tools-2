#ifndef __ProgOptions_H
#define __ProgOptions_H

#include <string>
#include "AutoDefine.h"

class ProgOptions
{
public:
	std::string m_inFileFullPath;

public:
	ProgOptions();
	void parseParam(int argc, char *argv[]);

	DECLARE_SET_GET_FUNC(std::string, inFileFullPath);
};

#endif