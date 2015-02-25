#ifndef __ArchiveData_H
#define __ArchiveData_H

/**
 * @brief 文件 Archive 数据结构
 */
#include "Prerequisites.h"
#include <io.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FileHeader;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	uint32 m_version;			// 版本
	uint32 m_fileCount;			// 文件总共数量
	uint32 m_fileSize;			// 文件总共大小
	FileHeaderVec* m_pFileVec;		// 整个文件列表

public:
	ArchiveData();
	~ArchiveData();

public:
	void ArchiveDir(const char* pDir);			// archive 某一个目录
	bool ArchiveData::fileHandle(const char* walkPath, struct _finddata_t* FileInfo);

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void writeFile();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif