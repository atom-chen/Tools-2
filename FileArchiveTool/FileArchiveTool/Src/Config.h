#ifndef __Config_H
#define __Config_H

#include <string>
#include "GlobalDefine.h"
#include "Platform.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Config
{
protected:
	std::string* m_pRootPath;		// �����������ˣ���˵��������Ŀ¼������ȫ�����

public:
	Config();
	~Config();

public:
	std::string& getRootPath();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif