#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;
class UnArchiveParam;
class ArchiveParam;
class PakPathSplitInfo;

/**
* @brief �ļ� Archive �ļ���ͷ��Ϣ
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8 m_pathLen;					// Ŀ¼���ȣ������� '\0'������ Utf-8 ����Ŀ¼���ȣ�������ǣ���Ҫ���� Utf-8 ���볤�ȣ������ַ����ĳ��ȣ��Ǵ洢�ռ�ĳ���
	char* m_pFullPath;					// �����ļ�Ŀ¼�����֣����� E:/aaa/bbb/ccc.txt
	char* m_fileNamePath;				// �����ļ����ֺ���չ�������� ccc.txt
	char* m_pakFileNamePath;			// ��������ʱ��д���ļ�ͷ������Դ����Ŀ¼������ bbb/ccc.txt

	uint32 m_fileOffset;				// �ļ������� Archive �е�ƫ��
	uint32 m_fileSize;					// �ļ���С
	uint32 m_flags;						// ��ʶ�ֶ�

public:
	FileHeader();
	~FileHeader();

public:
	void setFullPath(const char* dir, const char* fileName);
	char* getFullPath();
	void setFileName(const char* fileName);
	char* getFileName();
	char* getPakFileName();

	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2ArchiveFile(FILE* fileHandle);	// д�ļ�ͷ
	void writeFile2ArchiveFile(FILE* fileHandle);		// д���ļ�
	void readHeaderFromArchiveFile(MByteBuffer* ba);	// ��ȡ�ļ�ͷ��
	void writeArchiveFile2File(FILE* fileHandle, UnArchiveParam* pUnArchiveParam);

	uint32 getFileSize();
	void modifyArchiveFileName(ArchiveParam* pArchiveParam);		// �޸��ļ�����Ϊд�� Archive ���ļ�����

	// ��ʼ��һ�� FileHeader
	void initFileHeader(PakPathSplitInfo* pPakPathSplitInfo);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif