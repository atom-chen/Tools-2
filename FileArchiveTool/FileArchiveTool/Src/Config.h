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
	std::string* m_pBrowseRootPath;		// �����������ˣ���˵��������Ŀ¼������ȫ�����
	std::size_t m_maxSizePerPak;		// ÿһ����������С���ٴ���Ҫ���в�֣���λ���ֽڣ���ʼ��С��Ϊ 30M
	std::string* m_pakInRootPath;			// �����Ŀ¼
	std::string* m_pakOutputRootPath;		// �����Ŀ¼
	std::string* m_unpakOutputRootPath;		// �����Ŀ¼
	std::string* m_maniFestFullPath;		// �嵥�ļ��������Ŀ¼���ļ�����

public:
	Config();
	~Config();
	bool bCompress();	// �Ƿ�ʹ��ѹ��

public:
	std::string& getBrowseRootPath();
	std::string& getPakInRootPath();
	std::string& getPakOutputRootPath();
	std::string& getUnpakOutputRootPath();
	std::string& getManiFestFullPath();
	std::size_t getMaxSizePerPak();

	void loadConfig();
	bool isEqualInRootPath(std::string& path);
	bool isSubDirOfPakInRootPath(const char* path);	// �����Ŀ¼�Ƿ��� m_pakInRootPath ����Ŀ¼

protected:
	void parseEqualTokens(std::vector<std::string>& equalTokens);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif