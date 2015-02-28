#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;
class UnArchiveParam;
class ArchiveParam;

/**
* @brief 文件 Archive 文件的头信息
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8 m_pathLen;					// 目录长度，不包括 '\0'，都是 Utf-8 编码目录长度，如果不是，需要计算 Utf-8 编码长度，不是字符串的长度，是存储空间的长度
	char* m_pFullPath;
	char* m_fileNamePath;				// 文件路径名字
	uint32 m_fileOffset;				// 文件在整个 Archive 中的偏移
	uint32 m_fileSize;					// 文件大小

public:
	FileHeader();
	~FileHeader();

public:
	void setFullPath(const char* dir, const char* fileName);
	void setFileName(const char* fileName);

	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2ArchiveFile(FILE* fileHandle);	// 写文件头
	void writeFile2ArchiveFile(FILE* fileHandle);		// 写入文件
	void readHeaderFromArchiveFile(MByteBuffer* ba);	// 读取文件头部
	void writeArchiveFile2File(FILE* fileHandle, UnArchiveParam* pUnArchiveParam);

	uint32 getFileSize();
	void modifyArchiveFileName(ArchiveParam* pArchiveParam);		// 修改文件名字为写入 Archive 的文件名字
};

END_NAMESPACE_FILEARCHIVETOOL

#endif