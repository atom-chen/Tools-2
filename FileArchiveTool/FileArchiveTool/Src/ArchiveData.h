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
class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	ArchiveHeader* m_pArchiveHeader;
	uint32 m_fileSize;			// 文件总共大小
	FileHeaderVec* m_pFileVec;		// 整个文件列表

public:
	ArchiveData();
	~ArchiveData();

public:
	void adjustHeaderOffset();					// 修正每一个头文件的偏移
	void calcHeaderSize(uint32& headerSize);
	void ArchiveDir();			// archive 某一个目录
	void unArchiveFile();
	bool fileHandle(const char* walkPath, struct _finddata_t* FileInfo);

	void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif