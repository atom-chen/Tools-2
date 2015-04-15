#include "PakPathSplitInfo.h"
#include "FileArchiveToolSys.h"
#include "ArchiveParam.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakPathSplitInfo::PakPathSplitInfo() :
	m_bNeedPak(true)
{
	m_origPath = new std::string;
	m_pakName = new std::string;
	m_pakFilePath = new std::string;
	m_origFileName = new std::string;
}

PakPathSplitInfo::~PakPathSplitInfo()
{
	delete m_origPath;
	delete m_pakName;
	delete m_pakFilePath;
	delete m_origFileName;
}

void PakPathSplitInfo::initInfo(std::string& path, struct _finddata_t* FileInfo)
{
	*m_origPath = path;
	*m_origFileName = FileInfo->name;

	if (FileArchiveToolSysDef->getArchiveParamPtr()->isEqualArchiveDir(path))		// ����Ǵ����Ŀ¼
	{
		if (FileArchiveToolSysDef->getArchiveParamPtr()->getArchiveMode() == eArchiveMode_SubDir)		// ����Ǵ����Ŀ¼
		{
			m_bNeedPak = false;		// ��Ŀ¼�������Ŀ¼�µ�һ���ļ�ֱ�ӿ�����ȥ�������
			return;
		}
	}

	*m_pakFilePath = m_origPath->substr(strlen(FileArchiveToolSysDef->getArchiveParamPtr()->getArchiveDir()) + 1);
	*m_pakFilePath += "/";
	*m_pakFilePath += *m_origFileName;

	size_t findIdx = m_pakFilePath->find_first_of('/');
	*m_pakName = m_pakFilePath->substr(0, findIdx);
}

std::string& PakPathSplitInfo::getOrigPath()
{
	return *m_origPath;
}

std::string& PakPathSplitInfo::getPakName()
{
	return *m_pakName;
}

std::string& PakPathSplitInfo::getPakFilePath()
{
	return *m_pakFilePath;
}

std::size_t PakPathSplitInfo::getFileOrigSize()
{
	return m_fileOrigSize;
}

std::size_t PakPathSplitInfo::getFileCompressSize()
{
	return m_fileCompressSize;
}

std::string& PakPathSplitInfo::getOrigFileName()
{
	return *m_origFileName;
}

END_NAMESPACE_FILEARCHIVETOOL