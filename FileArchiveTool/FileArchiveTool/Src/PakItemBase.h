#ifndef __PakItemBase_H
#define __PakItemBase_H

/**
* @brief 一个数据包数据结构
*/
#include "Prerequisites.h"
#include <io.h>
#include <vector>
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;
class PakPathSplitInfo;
class FileHeader;

class FILEARCHIVETOOL_EXPORT PakItemBase
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	std::string* m_pakName;				// 生成的包的名字
	uint32 m_pakIdx;					// 同类型的包的索引
	ArchiveHeader* m_pArchiveHeader;	// 这个是总的文件头部信息

	uint32 m_fileSize;				// 文件总共大小
	FileHeaderVec* m_pFileVec;		// 整个文件列表
	std::string* m_fullPath;

public:
	PakItemBase();
	~PakItemBase();

public:
	void adjustHeaderOffset();					// 修正每一个头文件的偏移
	void calcHeaderSize(uint32& headerSize);
	void ArchiveDir();			// archive 某一个目录
	void unArchiveFile();

	void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// 是否可以将当前的文件添加到这个包里
	void addFileHeader(FileHeader* pFileHeader);				// 向包中添加一个文件
	void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);

	void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	void readArchiveFileHeader(const char* pFileName);

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif