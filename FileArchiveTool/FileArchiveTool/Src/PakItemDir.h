#ifndef __PakItemDir_H
#define __PakItemDir_H

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

class FILEARCHIVETOOL_EXPORT PakItemDir : public PakItemBase
{
protected:
	typedef std::vector<FileHeader*> FileHeaderVec;
	typedef std::vector<FileHeader*>::iterator FileHeaderVecIt;

protected:
	std::string* m_pakName;				// ���ɵİ������֣���������չ���֣����� aaa
	uint32 m_pakIdx;					// ͬ���͵İ�������
	std::string* m_pakFullName;			// �����ֺ���չ����������·���� ���� aaa_0.abc
	ArchiveHeader* m_pArchiveHeader;	// ������ܵ��ļ�ͷ����Ϣ

	uint32 m_fileSize;				// �ļ��ܹ���С
	FileHeaderVec* m_pFileVec;		// �����ļ��б�
	std::string* m_fullPath;		// �����������·�������֣����� E:/aaa/bbb/aaa_0.abc

public:
	PakItemDir(EPakItem ePakItem = ePI_DIR);
	virtual ~PakItemDir();

public:
	virtual void adjustHeaderOffset();					// ����ÿһ��ͷ�ļ���ƫ��
	virtual void calcHeaderSize(uint32& headerSize);

	virtual void asyncArchiveDir(ArchiveParam* m_pArchiveParam);
	virtual void asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam);

	virtual bool canAddFile(PakPathSplitInfo* pPakPathSplitInfo);		// �Ƿ���Խ���ǰ���ļ���ӵ��������
	virtual void addFileHeader(FileHeader* pFileHeader);				// ��������һ���ļ�
	virtual void initByPakPathSplitInfo(PakPathSplitInfo* m_pPakPathSplitInfo, uint32 packIdx);

	virtual void writeFile2ArchiveFile(ArchiveParam* pArchiveParam);
	virtual void readArchiveFileHeader(const char* pFileName);
	virtual bool isPakNameEqual(std::string& pakName);
	virtual void endOnePak();			// ������ǰ��һ����

	std::string& getPakFullName();

protected:
	virtual void clearFileVec();			// ���� m_pFileVec �е�����
	virtual void readArchiveFileHeader(FILE* fileHandle);
	virtual void writeArchiveFile2File(UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif