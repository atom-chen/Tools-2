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

enum FILEARCHIVETOOL_EXPORT EPakItem
{
	ePI_FILE,			// 文件
	ePI_DIR,			// 目录
};

class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;
class PakPathSplitInfo;
class FileHeader;

class FILEARCHIVETOOL_EXPORT PakItemBase
{
protected:
	EPakItem m_ePakItem;

public:
	PakItemBase(EPakItem ePakItem);
	virtual ~PakItemBase();

public:
	virtual void adjustHeaderOffset();					// 修正每一个头文件的偏移
	virtual void calcHeaderSize(uint32& headerSize);
	virtual void ArchiveDir();			// archive 某一个目录
	virtual void unArchiveFile();

	virtual void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	virtual void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// 是否可以将当前的文件添加到这个包里
	virtual void addFileHeader(FileHeader* pFileHeader);				// 向包中添加一个文件
	virtual void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);
	virtual void readArchiveFileHeader(const char* pFileName);
	virtual bool isPakNameEqual(std::string& pakName);
	virtual void endOnePak();

	EPakItem getPakItemType();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif