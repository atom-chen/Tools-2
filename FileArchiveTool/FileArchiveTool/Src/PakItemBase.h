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
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	std::string* m_pakName;				// ���ɵİ�������
	uint32 m_pakIdx;					// ͬ���͵İ�������
	ArchiveHeader* m_pArchiveHeader;	// ������ܵ��ļ�ͷ����Ϣ

	uint32 m_fileSize;				// �ļ��ܹ���С
	FileHeaderVec* m_pFileVec;		// �����ļ��б�
	std::string* m_fullPath;

public:
	PakItemBase();
	~PakItemBase();

public:
	void adjustHeaderOffset();					// ����ÿһ��ͷ�ļ���ƫ��
	void calcHeaderSize(uint32& headerSize);
	void ArchiveDir();			// archive ĳһ��Ŀ¼
	void unArchiveFile();

	void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// �Ƿ���Խ���ǰ���ļ���ӵ��������
	void addFileHeader(FileHeader* pFileHeader);				// ��������һ���ļ�
	void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);

	void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	void readArchiveFileHeader(const char* pFileName);

protected:
	void clearFileVec();			// ���� m_pFileVec �е�����
	void readArchiveFileHeader(FILE* fileHandle);
	void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif