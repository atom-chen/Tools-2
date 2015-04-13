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
	// ��ȡ��ǰ����Ŀ¼
	boost::filesystem::path old_cpath = boost::filesystem::current_path();	//ȡ�õ�ǰĿ¼
	// ��ȡ��ִ�о������ڵ�Ŀ¼�����Ҳ�ǵ�ǰ����Ŀ¼�����ܲ��ԣ�ֻ�ܴӴӿ����������õ�ǰ����Ŀ¼
	std::string fullpath;
	//fullpath = boost::filesystem::initial_path<boost::filesystem::path>().string();
	fullpath = old_cpath.string();

	FILE*fin = fopen(fullpath.c_str(), "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", fullpath.c_str());
		return;
	}

	// �����ļ���С
	fseek(fin, 0, SEEK_END);
	std::size_t fileLen = ftell(fin);
	char* pChar = new char[fileLen];
	fread((void*)pChar, 1, fileLen, fin);		// �����ֽڶ�ȡ����

	// �зָ�
	std::vector<std::string> linetokens;
	boost::split(linetokens, pChar, boost::is_any_of("\r\n|help"));
	delete[] pChar;
	// �Ⱥŷָ�
	std::vector<std::string> equalTokens;
	for (auto line : linetokens)
	{
		equalTokens.clear();
		boost::split(equalTokens, line, boost::is_any_of("="));

		// ��������
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