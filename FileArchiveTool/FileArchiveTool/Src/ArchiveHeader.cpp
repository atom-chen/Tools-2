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

	m_endian = sSysEndian;		// 0 大端 1 小端
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
	if (strncmp(m_magic, "asdf", sizeof(m_magic)) != 0)		// 检查 magic
	{
		return false;
	}

	// 读取 endian 
	fread(&m_endian, sizeof(m_endian), 1, fileHandle);
	pMByteBuffer->setEndian((SysEndian)m_endian);

	// 读取头部大小
	pMByteBuffer->setSize(sizeof(m_headerSize));		// 必然够 sizeof(m_headerSize) 个字节
	fread((void*)(pMByteBuffer->getStorage()), sizeof(m_headerSize), 1, fileHandle);
	pMByteBuffer->readUnsignedInt32(m_headerSize);
	pMByteBuffer->clear();

	pMByteBuffer->setSize(m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize));
	fread((void*)(pMByteBuffer->getStorage()), m_headerSize - sizeof(m_magic) - sizeof(m_endian) - sizeof(m_headerSize), 1, fileHandle);

	// 读取版本
	pMByteBuffer->readUnsignedInt32(m_version);
	// 读取文件数量
	pMByteBuffer->readUnsignedInt32(m_fileCount);

	return true;
}

void ArchiveHeader::writeArchiveFileHeader(FILE* fileHandle)
{
	// 写入 magic 
	fwrite(m_magic, sizeof(m_magic), 1, fileHandle);
	// 写入 endian 
	fwrite(&m_endian, sizeof(m_endian), 1, fileHandle);

	// 写入头部总共大小
	fwrite(&m_headerSize, sizeof(m_headerSize), 1, fileHandle);

	// 写入版本
	fwrite(&m_version, sizeof(m_version), 1, fileHandle);
	// 写入文件数量
	fwrite(&m_fileCount, sizeof(m_fileCount), 1, fileHandle);
}

uint32 ArchiveHeader::calcArchiveHeaderSizeNoFileHeader()
{
	// 写入 magic 
	// 写入 endian 
	// 写入头部总共大小
	// 写入版本
	// 写入文件数量
	return sizeof(m_magic) + sizeof(m_endian) + sizeof(m_headerSize) + sizeof(m_version) + sizeof(m_fileCount);
}


END_NAMESPACE_FILEARCHIVETOOL