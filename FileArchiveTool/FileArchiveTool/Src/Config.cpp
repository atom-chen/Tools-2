#include "Config.h"

#include <stdio.h>
#include <stdlib.h>

#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "FileArchiveToolSys.h"
#include "Util.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

Config::Config()
{
	m_pBrowseRootPath = new std::string("E:\\");
	m_outputRootPath = new std::string;
}

Config::~Config()
{
	delete m_pBrowseRootPath;
}

std::string& Config::getBrowseRootPath()
{
	return *m_pBrowseRootPath;
}

std::string& Config::getOutputRootPath()
{
	return *m_outputRootPath;
}

bool Config::bCompress()
{
	return true;
}

void Config::loadConfig()
{
	// 获取当前工作目录
	boost::filesystem::path cpath = boost::filesystem::current_path();	//取得当前目录
	cpath = cpath / "Config/Config.txt";		// 当前 Config 目录
	// 获取可执行镜像所在的目录，这个也是当前工作目录，可能不对，只能从从开发工具配置当前工作目录
	//fullpath = boost::filesystem::initial_path<boost::filesystem::path>().string();
	std::string fullpath = cpath.string();

	FILE*fin = fopen(fullpath.c_str(), "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", fullpath.c_str());
		return;
	}

	// 计算文件大小
	fseek(fin, 0, SEEK_END);	// 移动到文件结尾
	std::size_t fileLen = ftell(fin);	// 获取文件大小
	fseek(fin, 0, SEEK_SET);			// 移动到文件头部
	char* pChar = new char[fileLen + 1];
	pChar[fileLen] = 0;
	fread((void*)pChar, 1, fileLen, fin);		// 按照字节读取出来

	// 行分割
	std::vector<std::string> linetokens;
	std::string splitStr = "\r\n";
	//boost::split(linetokens, pChar, boost::is_any_of("\r\n"));		// 任何一个字符，注意 | 不是分割字符的， | 也是分隔符
	std::string lineStr = pChar;
	FileArchiveToolSysDef->getUtilPtr()->split(lineStr, splitStr, linetokens);
	delete[] pChar;
	// 等号分割
	std::vector<std::string> equalTokens;
	splitStr = "=";
	for (auto line : linetokens)
	{
		if (line.length() > 0)
		{
			equalTokens.clear();
			//boost::trim();
			//boost::split(equalTokens, line, boost::is_any_of("="));
			FileArchiveToolSysDef->getUtilPtr()->split(line, splitStr, equalTokens);
			// 解析配置
			parseEqualTokens(equalTokens);
		}
	}
}

void Config::parseEqualTokens(std::vector<std::string>& equalTokens)
{
	if (equalTokens[0] == "maxSizePerPak")
	{
		m_maxSizePerPak = strtol(equalTokens[0].c_str(), nullptr, 10);
	}
	else if (equalTokens[0] == "outputRootPath")
	{
		*m_outputRootPath = equalTokens[1];
		FileArchiveToolSysDef->getUtilPtr()->trim_right(*m_outputRootPath);
	}
}

std::size_t Config::getMaxSizePerPak()
{
	return m_maxSizePerPak;
}

END_NAMESPACE_FILEARCHIVETOOL