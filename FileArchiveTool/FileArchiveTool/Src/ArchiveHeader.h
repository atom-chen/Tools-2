#ifndef __ArchiveHeader_H
#define __ArchiveHeader_H

/**
 * @brief 文件 Archive 头部信息
 */
#include "Prerequisites.h"
#include <io.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;

class FILEARCHIVETOOL_EXPORT ArchiveHeader
{
public:
	char m_magic[4];			// 幻数
	uint8 m_endian;				// 大小端
	uint32 m_headerSize;		// 头部大小
	uint32 m_version;			// 版本
	uint32 m_fileCount;			// 文件总共数量

public:
	ArchiveHeader();
	~ArchiveHeader();

	void clear();
	void writeArchiveFileHeader(FILE* fileHandle);
	bool readArchiveFileHeader(FILE* fileHandle, MByteBuffer* pMByteBuffer);
	uint32 calcArchiveHeaderSizeNoFileHeader();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif