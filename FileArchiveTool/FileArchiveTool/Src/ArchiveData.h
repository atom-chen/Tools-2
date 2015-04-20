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
class PakItemBase;
class PakPathSplitInfo;
class PakStatInfo;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<PakItemBase*> PakItemVec;
	typedef std::vector<PakItemBase*>::iterator PakItemVecIt;

protected:
	PakItemVec* m_pPakItemVec;		// 整个文件包
	PakItemBase* m_curPak;				// 当前的包

	PakPathSplitInfo* m_pPakPathSplitInfo;		// 解析的文件信息，内部使用这个处理
	PakStatInfo* m_pPakStatInfo;				// 包的统计信息

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

	void removePakItem(PakItemBase* pPakItem);
	void removeUnPakItem(PakItemBase* pPakItem);
	size_t getPakItemCount();

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);

	void newPakItem();		// 新建一个 PakItem
	void addPakTask();	// 添加一打包任务
	void addUnPakTask();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif