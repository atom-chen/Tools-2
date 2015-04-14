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
	std::string* m_pRootPath;			// �����������ˣ���˵��������Ŀ¼������ȫ�����
	std::size_t m_maxSizePerPak;		// ÿһ����������С���ٴ���Ҫ���в�֣���λ���ֽ�
	std::string* m_outputRootPath;		// �����Ŀ¼

public:
	Config();
	~Config();
	bool bCompress();	// �Ƿ�ʹ��ѹ��

public:
	std::string& getRootPath();
	std::string& getOutputRootPath();
	std::size_t getMaxSizePerPak();

	void loadConfig();

protected:
	void parseEqualTokens(std::vector<std::string>& equalTokens);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif