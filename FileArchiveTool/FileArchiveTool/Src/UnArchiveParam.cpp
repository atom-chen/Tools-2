#include "UnArchiveParam.h"

#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

UnArchiveParam::UnArchiveParam(EPakParam ePakParam) :
	PakParam(ePakParam)
{
	m_punArchiveFilePath = new char[MAX_PATH];
	//m_punArchiveOutDir = new char[MAX_PATH];
}

UnArchiveParam::~UnArchiveParam()
{
	delete m_punArchiveFilePath;
	//delete m_punArchiveOutDir;
}

void UnArchiveParam::setUnArchiveFilePath(const char* pPath)
{
	memset(m_punArchiveFilePath, 0, MAX_PATH);
	strcpy(m_punArchiveFilePath, pPath);
}

//void UnArchiveParam::setUnArchiveOutDir(const char* pPath)
//{
//	memset(m_punArchiveOutDir, 0, MAX_PATH);
//	strcpy(m_punArchiveOutDir, pPath);
//}

const char* UnArchiveParam::getUnArchiveFilePath()
{
	return m_punArchiveFilePath;
}

//const char* UnArchiveParam::getUnArchiveOutDir()
//{
//	return m_punArchiveOutDir;
//}

END_NAMESPACE_FILEARCHIVETOOL