#ifndef __PakStatInfo_H
#define __PakStatInfo_H

/**
* @brief 这是一个统计包的信息数据
*/
#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT PakStatInfo
{
protected:
	uint32 m_pakCount;			// 包的数量
	uint32 m_curPakIdx;			// 当前包的索引，从 0 开始
	uint32 m_fileCount;			// 文件总共数量
	uint32 m_fileSize;			// 文件总共大小

public:
	PakStatInfo();
	~PakStatInfo();

	// 添加一个
	void addOnePak();
	void clearCurPakIdx();
	void addCurPakIdx();
	uint32 getCurPakIdx();
	void addOneFile();
	void addOneFileSize(uint32 fileSize);

	void clear();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif