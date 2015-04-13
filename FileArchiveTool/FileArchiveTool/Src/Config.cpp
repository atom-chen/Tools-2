#include "Config.h"
#include "boost/filesystem.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "boost/algorithm/string.hpp"

BEGIN_NAMESPACE_FILEARCHIVETOOL

Config::Config()
{
	m_pRootPath = new std::string("E:\\");
	loadConfig();
}

Config::~Config()
{
	delete m_pRootPath;
}

std::string& Config::getRootPath()
{
	return *m_pRootPath;
}

bool Config::bCompress()
{
	return true;
}

void Config::loadConfig()
{
	// 获取当前工作目录
	boost::filesystem::path old_cpath = boost::filesystem::current_path();	//取得当前目录
	// 获取可执行镜像所在的目录，这个也是当前工作目录，可能不对，只能从从开发工具配置当前工作目录
	std::string fullpath;
	//fullpath = boost::filesystem::initial_path<boost::filesystem::path>().string();
	fullpath = old_cpath.string();

	FILE*fin = fopen(fullpath.c_str(), "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", fullpath.c_str());
		return;
	}

	// 计算文件大小
	fseek(fin, 0, SEEK_END);
	std::size_t fileLen = ftell(fin);
	char* pChar = new char[fileLen];
	fread((void*)pChar, 1, fileLen, fin);		// 按照字节读取出来

	// 行分割
	std::vector<std::string> linetokens;
	boost::split(linetokens, pChar, boost::is_any_of("\r\n|help"));
	delete[] pChar;
	// 等号分割
	std::vector<std::string> equalTokens;
	for (auto line : linetokens)
	{
		equalTokens.clear();
		boost::split(equalTokens, line, boost::is_any_of("="));

		// 解析配置
		parseEqualTokens(equalTokens);
	}
}

void Config::parseEqualTokens(std::vector<std::string>& equalTokens)
{
	if (equalTokens[0] == "maxSizePerPak")
	{
		m_maxSizePerPak = strtol(equalTokens[0].c_str(), nullptr, 10);
	}
}

END_NAMESPACE_FILEARCHIVETOOL