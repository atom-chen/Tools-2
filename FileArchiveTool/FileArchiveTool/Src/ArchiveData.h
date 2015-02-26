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

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	char m_magic[4];			// ����
	uint8 m_endian;				// ��С��
	uint32 m_headerSize;		// ͷ����С
	uint32 m_version;			// �汾
	uint32 m_fileCount;			// �ļ��ܹ�����

	uint32 m_fileSize;			// �ļ��ܹ���С
	FileHeaderVec* m_pFileVec;		// �����ļ��б�

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
	void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif