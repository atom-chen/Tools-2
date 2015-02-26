#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;

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
	void writeHeader2File(FILE* fileHandle);	// д�ļ�ͷ
	void writeFile2File(FILE* fileHandle);		// д���ļ�

	void readHeaderFromFile(MByteBuffer* ba);	// ��ȡ�ļ�ͷ��
};

END_NAMESPACE_FILEARCHIVETOOL

#endif