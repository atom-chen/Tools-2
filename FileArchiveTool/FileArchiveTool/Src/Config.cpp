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
	// ��ȡ��ǰ����Ŀ¼
	boost::filesystem::path cpath = boost::filesystem::current_path();	//ȡ�õ�ǰĿ¼
	cpath = cpath / "Config/Config.txt";		// ��ǰ Config Ŀ¼
	// ��ȡ��ִ�о������ڵ�Ŀ¼�����Ҳ�ǵ�ǰ����Ŀ¼�����ܲ��ԣ�ֻ�ܴӴӿ����������õ�ǰ����Ŀ¼
	//fullpath = boost::filesystem::initial_path<boost::filesystem::path>().string();
	std::string fullpath = cpath.string();

	FILE*fin = fopen(fullpath.c_str(), "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", fullpath.c_str());
		return;
	}

	// �����ļ���С
	fseek(fin, 0, SEEK_END);	// �ƶ����ļ���β
	std::size_t fileLen = ftell(fin);	// ��ȡ�ļ���С
	fseek(fin, 0, SEEK_SET);			// �ƶ����ļ�ͷ��
	char* pChar = new char[fileLen + 1];
	pChar[fileLen] = 0;
	fread((void*)pChar, 1, fileLen, fin);		// �����ֽڶ�ȡ����

	// �зָ�
	std::vector<std::string> linetokens;
	std::string splitStr = "\r\n";
	//boost::split(linetokens, pChar, boost::is_any_of("\r\n"));		// �κ�һ���ַ���ע�� | ���Ƿָ��ַ��ģ� | Ҳ�Ƿָ���
	std::string lineStr = pChar;
	FileArchiveToolSysDef->getUtilPtr()->split(lineStr, splitStr, linetokens);
	delete[] pChar;
	// �Ⱥŷָ�
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
			// ��������
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