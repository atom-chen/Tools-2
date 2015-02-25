#ifndef __ArchiveData_H
#define __ArchiveData_H

/**
 * @brief 文件 Archive 数据结构
 */
#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	uint32 m_version;			// 版本
	uint32 m_fileCount;			// 文件总共数量

public:
	ArchiveData();
	~ArchiveData();

public:
	void ArchiveDir(const char* pDir);			// archive 某一个目录
};

END_NAMESPACE_FILEARCHIVETOOL

#endif