#ifndef __PakItem_H
#define __PakItem_H

/**
* @brief һ�����ݰ����ݽṹ
*/
#include "Prerequisites.h"
#include <io.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FileHeader;
class ArchiveParam;
class UnArchiveParam;
class ArchiveHeader;

class FILEARCHIVETOOL_EXPORT PakItem
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	ArchiveHeader* m_pArchiveHeader;
	uint32 m_fileSize;			// �ļ��ܹ���С
	FileHeaderVec* m_pFileVec;		// �����ļ��б�

public:
	PakItem();
	~PakItem();

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
	void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif