#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;

/**
* @brief 文件 Archive 文件的头信息
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
public:
	uint8 m_pathLen;					// 目录长度，不包括 '\0'
	char* m_pFullPath;
	char* m_fileNamePath;		// 文件路径名字
	uint32 m_fileOffset;				// 文件在整个 Archive 中的偏移
	uint32 m_fileSize;					// 文件大小

public:
	FileHeader();
	~FileHeader();

public:
	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2File(FILE* fileHandle);	// 写文件头
	void writeFile2File(FILE* fileHandle);		// 写入文件

	void readHeaderFromFile(MByteBuffer* ba);	// 读取文件头部
};

END_NAMESPACE_FILEARCHIVETOOL

#endif