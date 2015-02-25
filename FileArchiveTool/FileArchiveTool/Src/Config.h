#ifndef __Config_H
#define __Config_H

#include <string>
#include "GlobalDefine.h"
#include "Platform.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Config
{
protected:
	std::string* m_pRootPath;		// 如果这个设置了，就说明浏览这个目录，否则全盘浏览

public:
	Config();
	~Config();

public:
	std::string& getRootPath();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif