#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;
class UnArchiveParam;

/**
* @brief �ļ� Archive �ļ���ͷ��Ϣ
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
public:
	uint8 m_pathLen;					// Ŀ¼���ȣ������� '\0'
	char* m_pFullPath;
	char* m_fileNamePath;		// �ļ�·������
	uint32 m_fileOffset;				// �ļ������� Archive �е�ƫ��
	uint32 m_fileSize;					// �ļ���С

public:
	FileHeader();
	~FileHeader();

public:
	uint32 calcHeaderSize();
	void adjustHeaderOffset(uint32 offset);
	void writeHeader2ArchiveFile(FILE* fileHandle);	// д�ļ�ͷ
	void writeFile2ArchiveFile(FILE* fileHandle, uint32 sizePerOne, char* pchar);		// д���ļ�
	void readHeaderFromArchiveFile(MByteBuffer* ba);	// ��ȡ�ļ�ͷ��
	void writeArchiveFile2File(FILE* fileHandle, uint32 sizePerOne, char* pchar, UnArchiveParam* pUnArchiveParam);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif