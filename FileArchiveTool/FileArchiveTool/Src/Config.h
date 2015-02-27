#ifndef __Config_H
#define __Config_H

#include <string>
#include "Prerequisites.h"
#include "FileArchiveToolSys.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Config
{
public:
	friend FileArchiveToolSys;

protected:
	std::string* m_pRootPath;		// 如果这个设置了，就说明浏览这个目录，否则全盘浏览

public:
	Config();
	~Config();
	bool bCompress();	// 是否使用压缩

public:
	std::string& getRootPath();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif