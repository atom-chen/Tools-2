#ifndef __ProgOptions_H
#define __ProgOptions_H

#include <string>
#include "AutoDefine.h"

class ProgOptions
{
public:
	std::string m_inFileFullPath;
	std::string m_outMeshXmlFullPath;
	std::string m_outSkeletonXmlFullPath;

public:
	ProgOptions();
	void parseParam(int argc, char *argv[]);

	DECLARE_SET_GET_FUNC(std::string, inFileFullPath);
	DECLARE_SET_GET_FUNC(std::string, outMeshXmlFullPath);
	DECLARE_SET_GET_FUNC(std::string, outSkeletonXmlFullPath);
};

#endif