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
	char m_magic[4];			// 幻数
	uint8 m_endian;				// 大小端
	uint32 m_headerSize;		// 头部大小
	uint32 m_version;			// 版本
	uint32 m_fileCount;			// 文件总共数量

	uint32 m_fileSize;			// 文件总共大小
	FileHeaderVec* m_pFileVec;		// 整个文件列表

public:
	ArchiveData();
	~ArchiveData();

public:
	void adjustHeaderOffset();					// 修正每一个头文件的偏移
	void calcHeaderSize(uint32& headerSize);
	void ArchiveDir(const char* pDir);			// archive 某一个目录
	void unArchiveFile(const char* pFileName);
	bool fileHandle(const char* walkPath, struct _finddata_t* FileInfo);

	void asyncArchiveDir(const char* pDir);

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void writeFile2ArchiveFile(const char* pFileName);
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(const char* pFileName);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif