#ifndef __PakItemDir_H
#define __PakItemDir_H

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

class FILEARCHIVETOOL_EXPORT PakItemDir : public PakItemBase
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	std::string* m_pakName;				// 生成的包的名字，不包括扩展名字，例如 aaa
	uint32 m_pakIdx;					// 同类型的包的索引
	std::string* m_pakFullName;			// 包名字和扩展名，不包括路径， 例如 aaa_0.abc
	ArchiveHeader* m_pArchiveHeader;	// 这个是总的文件头部信息

	uint32 m_fileSize;				// 文件总共大小
	FileHeaderVec* m_pFileVec;		// 整个文件列表
	std::string* m_fullPath;		// 包输出的完整路径和名字，例如 E:/aaa/bbb/aaa_0.abc

public:
	PakItemDir(EPakItem ePakItem = ePI_DIR);
	virtual ~PakItemDir();

public:
	virtual void adjustHeaderOffset();					// 修正每一个头文件的偏移
	virtual void calcHeaderSize(uint32& headerSize);

	virtual void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	virtual void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// 是否可以将当前的文件添加到这个包里
	virtual void addFileHeader(FileHeader* pFileHeader);				// 向包中添加一个文件
	virtual void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);

	virtual void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	virtual void readArchiveFileHeader(const char* pFileName);
	virtual bool isPakNameEqual(std::string& pakName);
	virtual void endOnePak();			// 结束当前的一个包

	std::string& getPakFullName();

protected:
	virtual void clearFileVec();			// 清理 m_pFileVec 中的内容
	virtual void readArchiveFileHeader(FILE* fileHandle);
	virtual void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif