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
class PakItemBase;
class PakPathSplitInfo;
class PakStatInfo;
class ArchiveParam;
class UnArchiveParam;
class PakParam;

class FILEARCHIVETOOL_EXPORT ArchiveData
{
protected:
	typedef std::vector<PakItemBase*> PakItemVec;
	typedef std::vector<PakItemBase*>::iterator PakItemVecIt;

	typedef std::vector<PakParam*> PakParamVec;
	typedef std::vector<PakParam*>::iterator PakParamVecIt;

protected:
	PakItemVec* m_pPakItemVec;		// �����ļ���
	PakItemBase* m_curPak;				// ��ǰ�İ�

	PakPathSplitInfo* m_pPakPathSplitInfo;		// �������ļ���Ϣ���ڲ�ʹ���������
	PakStatInfo* m_pPakStatInfo;				// ����ͳ����Ϣ

	PakParamVec* m_pPakParamVec;					// ��������б�
	PakParam* m_pCurParam;

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

	void removePakItem(PakItemBase* pPakItem);
	void removeUnPakItem(PakItemBase* pPakItem);
	size_t getPakItemCount();

	ArchiveParam* getArchiveParamPtr();
	UnArchiveParam* getUnArchiveParamPtr();

	void addArchiveParamPtr(ArchiveParam* pArchiveParam);
	void addUnArchiveParamPtr(UnArchiveParam* pUnArchiveParam);
	void onManiFestEnd();			// �嵥���������˵��һ����������Ľ�����

protected:
	void clearFileVec();			// ���� m_pFileVec �е�����
	void readArchiveFileHeader(const char* pFileName);
	void readArchiveFileHeader(FILE* fileHandle);

	void newPakItem();		// �½�һ�� PakItem
	void addPakTask();	// ���һ�������
	void addUnPakTask();

	void removeArchiveParamPtr();
	void removeUnArchiveParamPtr();
	void handleNextPakParam();				// ������һ���ȴ������ Param
	bool hasNextPakParam();					// �Ƿ���δ����� Param
};

END_NAMESPACE_FILEARCHIVETOOL

#endif