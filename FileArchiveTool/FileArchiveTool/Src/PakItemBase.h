#ifndef __PakItemBase_H
#define __PakItemBase_H

/**
* @brief һ�����ݰ����ݽṹ
*/
#include "Prerequisites.h"
#include <io.h>
#include <vector>
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;
class PakPathSplitInfo;
class FileHeader;

class FILEARCHIVETOOL_EXPORT PakItemBase
{
public:
	PakItemBase();
	virtual ~PakItemBase();

public:
	virtual void adjustHeaderOffset();					// ����ÿһ��ͷ�ļ���ƫ��
	virtual void calcHeaderSize(uint32& headerSize);
	virtual void ArchiveDir();			// archive ĳһ��Ŀ¼
	virtual void unArchiveFile();

	virtual void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	virtual void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// �Ƿ���Խ���ǰ���ļ���ӵ��������
	virtual void addFileHeader(FileHeader* pFileHeader);				// ��������һ���ļ�
	virtual void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);
	virtual void readArchiveFileHeader(const char* pFileName);
	virtual bool isPakNameEqual(std::string& pakName);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif