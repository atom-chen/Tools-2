#ifndef __FileInfo_H
#define __FileInfo_H

#include <string>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
* @brief �ļ� Archive �ļ���ͷ��Ϣ
*/
class FILEARCHIVETOOL_EXPORT FileHeader
{
protected:
	uint8	m_pathLen;					// Ŀ¼���ȣ������� '\0'
	std::string* m_fileNamePath;		// �ļ�·������
	uint32 m_fileSize;					// �ļ���С
	uint32 m_fileOffset;				// �ļ������� Archive �е�ƫ��

public:
	FileHeader();
	~FileHeader();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif