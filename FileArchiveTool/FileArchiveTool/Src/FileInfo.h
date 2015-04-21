#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;
class UnArchiveParam;
class ArchiveParam;
class PakPathSplitInfo;

/**
* @brief 文件 Archive 文件的头信息
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8 m_pathLen;					// 目录长度，不包括 '\0'，都是 Utf-8 编码目录长度，如果不是，需要计算 Utf-8 编码长度，不是字符串的长度，是存储空间的长度
	char* m_pFullPath;					// 完整文件目录和名字，例如 E:/aaa/bbb/ccc.txt
	char* m_fileNamePath;				// 就是文件名字和扩展名，例如 ccc.txt
	char* m_pakFileNamePath;			// 打包输出的时候写入文件头部的资源查找目录，例如 bbb/ccc.txt

	uint32 m_fileOffset;				// 文件在整个 Archive 中的偏移
	uint32 m_fileSize;					// 文件大小
	uint32 m_flags;						// 标识字段

public:
	FileHeader();
	~FileHeader();

public:
	void setFullPath(const char* dir, const char* fileName);
	char* getFullPath();
	void setFileName(const char* fileName);
	char* getFileName();
	char* getPakFileName();

	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2ArchiveFile(FILE* fileHandle);	// 写文件头
	void writeFile2ArchiveFile(FILE* fileHandle);		// 写入文件
	void readHeaderFromArchiveFile(MByteBuffer* ba);	// 读取文件头部
	void writeArchiveFile2File(FILE* fileHandle, UnArchiveParam* pUnArchiveParam);

	uint32 getFileSize();
	void modifyArchiveFileName(ArchiveParam* pArchiveParam);		// 修改文件名字为写入 Archive 的文件名字

	// 初始化一个 FileHeader
	void initFileHeader(PakPathSplitInfo* pPakPathSplitInfo);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif