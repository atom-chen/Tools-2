#ifndef __Config_H
#define __Config_H

#include <string>
#include "Prerequisites.h"
#include "FileArchiveToolSys.h"
#include <stddef.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Config
{
public:
	friend FileArchiveToolSys;

protected:
	std::string* m_pRootPath;		// �����������ˣ���˵��������Ŀ¼������ȫ�����
	std::size_t m_maxSizePerPak;		// ÿһ����������С���ٴ���Ҫ���в�֣���λ���ֽ�

public:
	Config();
	~Config();
	bool bCompress();	// �Ƿ�ʹ��ѹ��

public:
	std::string& getRootPath();
	void loadConfig();

protected:
	void parseEqualTokens(std::vector<std::string>& equalTokens);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif