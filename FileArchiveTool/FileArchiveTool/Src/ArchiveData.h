#ifndef __ArchiveData_H
#define __ArchiveData_H

/**
 * @brief �ļ� Archive ���ݽṹ
 */
#include "Prerequisites.h"
#include <io.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FileHeader;
class ArchiveParam;
class UnArchiveParam;
class PakItem;
class PakPathSplitInfo;
class PakStatInfo;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<PakItem*> PakItemVec;
	typedef std::vector<PakItem*>::iterator PakItemVecIt;

protected:
	PakItemVec* m_pPakItemVec;		// �����ļ���
	PakItem* m_curPak;				// ��ǰ�İ�

	PakPathSplitInfo* m_pPakPathSplitInfo;		// �������ļ���Ϣ���ڲ�ʹ���������
	PakStatInfo* m_pPakStatInfo;				// ����ͳ����Ϣ

public:
	ArchiveData();
	~ArchiveData();

public:
	void adjustHeaderOffset();					// ����ÿһ��ͷ�ļ���ƫ��
	void calcHeaderSize(uint32& headerSize);
	void ArchiveDir();			// archive ĳһ��Ŀ¼
	void unArchiveFile();
	bool fileHandle(const char* walkPath, struct _finddata_t* FileInfo);

	void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

protected:
	void clearFileVec();			// ���� m_pFileVec �е�����
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);

	void newPakItem();		// �½�һ�� PakItem
};

END_NAMESPACE_FILEARCHIVETOOL

#endif