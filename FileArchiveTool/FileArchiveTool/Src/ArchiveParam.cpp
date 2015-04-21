#include "ArchiveParam.h"
#include "FileArchiveToolSys.h"
#include "Config.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

ArchiveParam::ArchiveParam(EPakParam ePakParam) :
	PakParam(ePakParam)
{
	m_pArchiveDir = new char[MAX_PATH];
	//m_pArchiveFilePath = new char[MAX_PATH];
}

ArchiveParam::~ArchiveParam()
{
	delete m_pArchiveDir;
	//delete m_pArchiveFilePath;
}

void ArchiveParam::setArchiveDir(const char* pPath)
{
	memset(m_pArchiveDir, 0, MAX_PATH);
	strcpy(m_pArchiveDir, pPath);
}

//void ArchiveParam::setArchiveFilePath(const char* pPath)
//{
//	memset(m_pArchiveFilePath, 0, MAX_PATH);
//	strcpy(m_pArchiveFilePath, pPath);
//}

const char* ArchiveParam::getArchiveDir()
{
	return m_pArchiveDir;
}

//const char* ArchiveParam::getArchiveFilePath()
//{
//	return m_pArchiveFilePath;
//}

bool ArchiveParam::isEqualArchiveDir(std::string& path)
{
	if (path.length() == strlen(m_pArchiveDir))
	{
		if (strcmp(path.c_str(), m_pArchiveDir) == 0)
		{
			return true;
		}
	}

	return false;
}

//void ArchiveParam::setArchiveMode(ArchiveMode mode)
//{
//	m_eArchiveMode = mode;
//}

ArchiveMode ArchiveParam::getArchiveMode()
{
	if (strncmp(m_pArchiveDir, FileArchiveToolSysDef->getConfigPtr()->getPakInRootPath().c_str(), strlen(m_pArchiveDir) != 0))
	{
		return eArchiveMode_SubDir;
	}

	return eArchiveMode_RootDir;
}

END_NAMESPACE_FILEARCHIVETOOL