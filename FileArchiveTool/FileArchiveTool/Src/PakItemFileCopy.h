#ifndef __PakItemFileCopy_H
#define __PakItemFileCopy_H

/**
* @brief һ�����ݰ����ݽṹ
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

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// �Ƿ���Խ���ǰ���ļ���ӵ��������
	virtual void addFileHeader(FileHeader* pFileHeader);				// ��������һ���ļ�
	virtual void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	virtual void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif