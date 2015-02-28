#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;
class UnArchiveParam;
class ArchiveParam;

/**
* @brief �ļ� Archive �ļ���ͷ��Ϣ
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8 m_pathLen;					// Ŀ¼���ȣ������� '\0'������ Utf-8 ����Ŀ¼���ȣ�������ǣ���Ҫ���� Utf-8 ���볤�ȣ������ַ����ĳ��ȣ��Ǵ洢�ռ�ĳ���
	char* m_pFullPath;
	char* m_fileNamePath;				// �ļ�·������
	uint32 m_fileOffset;				// �ļ������� Archive �е�ƫ��
	uint32 m_fileSize;					// �ļ���С

public:
	FileHeader();
	~FileHeader();

public:
	void setFullPath(const char* dir, const char* fileName);
	void setFileName(const char* fileName);

	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2ArchiveFile(FILE* fileHandle);	// д�ļ�ͷ
	void writeFile2ArchiveFile(FILE* fileHandle);		// д���ļ�
	void readHeaderFromArchiveFile(MByteBuffer* ba);	// ��ȡ�ļ�ͷ��
	void writeArchiveFile2File(FILE* fileHandle, UnArchiveParam* pUnArchiveParam);

	uint32 getFileSize();
	void modifyArchiveFileName(ArchiveParam* pArchiveParam);		// �޸��ļ�����Ϊд�� Archive ���ļ�����
};

END_NAMESPACE_FILEARCHIVETOOL

#endif