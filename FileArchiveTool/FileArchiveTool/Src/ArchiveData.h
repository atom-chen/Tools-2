#ifndef __ArchiveData_H
#define __ArchiveData_H

/**
 * @brief �ļ� Archive ���ݽṹ
 */
#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	uint32 m_version;			// �汾
	uint32 m_fileCount;			// �ļ��ܹ�����

public:
	ArchiveData();
	~ArchiveData();

public:
	void ArchiveDir(const char* pDir);			// archive ĳһ��Ŀ¼
};

END_NAMESPACE_FILEARCHIVETOOL

#endif