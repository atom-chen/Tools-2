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
	std::string* m_pRootPath;		// �����������ˣ���˵��������Ŀ¼������ȫ�����

public:
	Config();
	~Config();
	bool bCompress();	// �Ƿ�ʹ��ѹ��

public:
	std::string& getRootPath();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif