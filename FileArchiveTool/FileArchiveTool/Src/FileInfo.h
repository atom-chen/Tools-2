#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
* @brief 文件 Archive 文件的头信息
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8	m_pathLen;					// 目录长度，不包括 '\0'
	std::string* m_fileNamePath;		// 文件路径名字
	uint32 m_fileSize;					// 文件大小
	uint32 m_fileOffset;				// 文件在整个 Archive 中的偏移

public:
	FileHeader();
	~FileHeader();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif