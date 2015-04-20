#include "ArchiveHeader.h"
#include "Version.h"
#include "SystemEndian.h"
#include "MByteBuffer.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveHeader::ArchiveHeader() :
	m_version(ARCHIVETOOL_VERSION), m_headerSize(0), m_fileCount(0)
{
	m_magic[0] = 'a';
	m_magic[1] = 's';
	m_magic[2] = 'd';
	m_magic[3] = 'f';

	m_endian = sSysEndian;		// 0 ��� 1 С��
}

ArchiveHeader::~ArchiveHeader()
{

}

void ArchiveHeader::clear()
{
	m_fileCount = 0;
	m_headerSize = 0;
}

bool ArchiveHeader::readArchiveFileHeader(FILE* fileHandle, MByteBuffer* pMByteBuffer)
{
	fread(m_magic, sizeof(m_magic), 1, fileHandle);
	if (strncmp(m_magic, "asdf", sizeof(m_magic)) != 0)		// ��� magic
	{
		return false;
	}

	// ��ȡ endian 
	fread(&m_endian, sizeof(m_endian), 1, fileHandle);
	pMByteBuffer->setEndian((SysEndian)m_endian);

	// ��ȡͷ����С
	pMByteBuffer->setSize(sizeof(m_headerSize));		// ��Ȼ�� sizeof(m_headerSize) ���ֽ�
	fread((void*)(pMByteBuffer->getStorage()), sizeof(m_headerSize), 1, fileHandle);
	pMByteBuffer->readUnsignedInt32(m_headerSize);
	pMByteBuffer->clear();

	pMByteBuffer->setSize(m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize));
	fread((void*)(pMByteBuffer->getStorage()), m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize), 1, fileHandle);

	// ��ȡ�汾
	pMByteBuffer->readUnsignedInt32(m_version);
	// ��ȡ�ļ�����
	pMByteBuffer->readUnsignedInt32(m_fileCount);

	return true;
}

void ArchiveHeader::writeArchiveFileHeader(FILE* fileHandle)
{
	// д�� magic 
	fwrite(m_magic, sizeof(m_magic), 1, fileHandle);
	// д�� endian 
	fwrite(&m_endian, sizeof(m_endian), 1, fileHandle);

	// д��ͷ���ܹ���С
	fwrite(&m_headerSize, sizeof(m_headerSize), 1, fileHandle);

	// д��汾
	fwrite(&m_version, sizeof(m_version), 1, fileHandle);
	// д���ļ�����
	fwrite(&m_fileCount, sizeof(m_fileCount), 1, fileHandle);
}

uint32 ArchiveHeader::calcArchiveHeaderSizeNoFileHeader()
{
	// д�� magic 
	// д�� endian 
	// д��ͷ���ܹ���С
	// д��汾
	// д���ļ�����
	return sizeof(m_magic) + sizeof(m_endian) + sizeof(m_headerSize) + sizeof(m_version) + sizeof(m_fileCount);
}


END_NAMESPACE_FILEARCHIVETOOL