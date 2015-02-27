#ifndef __ArchiveHeader_H
#define __ArchiveHeader_H

/**
 * @brief �ļ� Archive ͷ����Ϣ
 */
#include "Prerequisites.h"
#include <io.h>
#include <vector>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class MByteBuffer;

class FILEARCHIVETOOL_EXPORT ArchiveHeader
{
public:
	char m_magic[4];			// ����
	uint8 m_endian;				// ��С��
	uint32 m_headerSize;		// ͷ����С
	uint32 m_version;			// �汾
	uint32 m_fileCount;			// �ļ��ܹ�����

public:
	ArchiveHeader();
	~ArchiveHeader();

	void clear();
	void writeArchiveFileHeader(FILE* fileHandle);
	bool readArchiveFileHeader(FILE* fileHandle, MByteBuffer* pMByteBuffer);
	uint32 calcArchiveHeaderSizeNoFileHeader();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif