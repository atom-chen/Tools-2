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
class ArchiveParam;
class UnArchiveParam;
class PakParam;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<PakItemBase*> PakItemVec;
	typedef std::vector<PakItemBase*>::iterator PakItemVecIt;

	typedef std::vector<PakParam*> PakParamVec;
	typedef std::vector<PakParam*>::iterator PakParamVecIt;

protected:
	PakItemVec* m_pPakItemVec;		// 整个文件包
	PakItemBase* m_curPak;				// 当前的包

	PakPathSplitInfo* m_pPakPathSplitInfo;		// 解析的文件信息，内部使用这个处理
	PakStatInfo* m_pPakStatInfo;				// 包的统计信息

	PakParamVec* m_pPakParamVec;					// 打包参数列表
	PakParam* m_pCurParam;

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

	ArchiveParam* getArchiveParamPtr();
	UnArchiveParam* getUnArchiveParamPtr();

	void addArchiveParamPtr(ArchiveParam* pArchiveParam);
	void addUnArchiveParamPtr(UnArchiveParam* pUnArchiveParam);
	void onManiFestEnd();			// 清单输出结束，说明一个打包真正的结束了

protected:
	void clearFileVec();			// 清理 m_pFileVec 中的内容
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);

	void newPakItem();		// 新建一个 PakItem
	void addPakTask();	// 添加一打包任务
	void addUnPakTask();

	void removeArchiveParamPtr();
	void removeUnArchiveParamPtr();
	void handleNextPakParam();				// 处理下一个等待处理的 Param
	bool hasNextPakParam();					// 是否有未处理的 Param
};

END_NAMESPACE_FILEARCHIVETOOL

#endif