#include "PakItemFileCopy.h"
#include "FileArchiveToolSys.h"
#include "Util.h"
#include "FileInfo.h"
#include "Version.h"
#include "SystemEndian.h"
#include "MByteBuffer.h"
#include "BufferDefaultValue.h"
#include "ArchiveTask.h"
#include "TaskQueue.h"
#include "ArchiveParam.h"
#include "UnArchiveParam.h"
#include "UnArchiveTask.h"
#include "Config.h"
#include "ArchiveHeader.h"
#include "PakPathSplitInfo.h"
#include "PakTask.h"
#include "LogSys.h"

#include <sstream>

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakItemFileCopy::PakItemFileCopy():
	m_pFileHeader(nullptr)
{
}

PakItemFileCopy::~PakItemFileCopy()
{
}

void PakItemFileCopy::asyncArchiveDir(ArchiveParam* pArchiveParam)
{
	std::stringstream ss;//����һ����
	ss.clear();
	ss.str("");

	ss << "��ʼ����ļ�\n";
	ss << "�ļ�����:\n";
	ss << m_pFileHeader->getFullPath() << "\n";
	ss << "��������ļ�\n";
	FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

	PakItemBase::asyncArchiveDir(pArchiveParam);
	writeFile2ArchiveFile(pArchiveParam);
}

void PakItemFileCopy::asyncUnArchiveFile(UnArchiveParam* pUnArchiveParam)
{
	PakItemBase::asyncUnArchiveFile(pUnArchiveParam);
	writeArchiveFile2File(pUnArchiveParam);
}

#define BUF_SIZE    256
// д���ļ�
void PakItemFileCopy::writeFile2ArchiveFile(ArchiveParam* pArchiveParam)
{
	std::string outPath = FileArchiveToolSysDef->getConfigPtr()->getOutputRootPath() + "/" + m_pFileHeader->getFileName();
	std::string inPath = m_pFileHeader->getFullPath();

	FILE* outFileHandle = fopen(outPath.c_str(), "wb");
	FILE* inFileHandle = fopen(inPath.c_str(), "rb");

	size_t bytes_in, bytes_out;
	long len = 0;
	char* data = new char[256];

	while ((bytes_in = fread(data, 1, BUF_SIZE, inFileHandle)) > 0)
	{
		bytes_out = fwrite(data, 1, bytes_in, outFileHandle);
		if (bytes_in != bytes_out)
		{
			// ���������˳�
			break;
		}
		len += bytes_out;
	}

	fclose(inFileHandle);
	fclose(outFileHandle);
}

void PakItemFileCopy::writeArchiveFile2File(UnArchiveParam* pUnArchiveParam)
{

}

bool PakItemFileCopy::canAddFile(PakPathSplitInfo* pPakPathSplitInfo)
{
	return false;
}

void PakItemFileCopy::addFileHeader(FileHeader* pFileHeader)
{
	std::stringstream ss;//����һ����
	ss.clear();
	ss.str("");

	ss << "��ӵ����ļ�[" << pFileHeader->getFullPath() << "]\n";
	FileArchiveToolSysDef->getLogSysPtr()->log(ss.str().c_str());

	m_pFileHeader = pFileHeader;
}

END_NAMESPACE_FILEARCHIVETOOL