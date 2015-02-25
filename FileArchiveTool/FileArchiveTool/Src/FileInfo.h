#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>
#include <io.h>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
* @brief �ļ� Archive �ļ���ͷ��Ϣ
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
public:
	uint8	m_pathLen;					// Ŀ¼���ȣ������� '\0'
	std::string* m_fileNamePath;		// �ļ�·������
	uint32 m_fileOffset;				// �ļ������� Archive �е�ƫ��
	uint32 m_fileSize;					// �ļ���С

public:
	FileHeader();
	~FileHeader();

public:
	uint32 calcHeaderSize();
	void writeHeader2File(FILE* fileHandle);
	void writeFile2File(FILE* fileHandle);		// д���ļ�
};

END_NAMESPACE_FILEARCHIVETOOL

#endif