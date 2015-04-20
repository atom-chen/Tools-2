#ifndef __Config_H
#define __Config_H

#include "Prerequisites.h"
#include "FileArchiveToolSys.h"

#include <string>
#include <stddef.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Config
{
public:
	friend FileArchiveToolSys;

protected:
	std::string* m_pBrowseRootPath;		// 如果这个设置了，就说明浏览这个目录，否则全盘浏览
	std::size_t m_maxSizePerPak;		// 每一个包的最大大小，再大需要进行拆分，单位是字节，初始大小定为 30M
	std::string* m_pakInRootPath;			// 输入根目录
	std::string* m_pakOutputRootPath;		// 输出根目录
	std::string* m_unpakOutputRootPath;		// 输出根目录

public:
	Config();
	~Config();
	bool bCompress();	// 是否使用压缩

public:
	std::string& getBrowseRootPath();
	std::string& getPakInRootPath();
	std::string& getPakOutputRootPath();
	std::string& getUnpakOutputRootPath();
	std::size_t getMaxSizePerPak();

	void loadConfig();
	bool isEqualInRootPath(std::string& path);

protected:
	void parseEqualTokens(std::vector<std::string>& equalTokens);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif