#ifndef __PakItemFileCopy_H
#define __PakItemFileCopy_H

/**
* @brief 一个数据包数据结构
*/
#include "Prerequisites.h"
#include "PakItemBase.h"

#include <io.h>
#include <vector>
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;
class PakPathSplitInfo;
class FileHeader;

class FILEARCHIVETOOL_EXPORT PakItemFileCopy : public PakItemBase
{
protected:
	FileHeader* m_pFileHeader;

public:
	PakItemFileCopy(EPakItem ePakItem = ePI_FILE);
	virtual ~PakItemFileCopy();

public:
	virtual void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	virtual void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// 是否可以将当前的文件添加到这个包里
	virtual void addFileHeader(FileHeader* pFileHeader);				// 向包中添加一个文件
	virtual void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	virtual void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif