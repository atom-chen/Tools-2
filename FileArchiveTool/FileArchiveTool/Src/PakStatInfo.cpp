#include "PakStatInfo.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

PakStatInfo::PakStatInfo() : 
	m_pakCount(0), m_curPakIdx(0), m_fileCount(0), m_fileSize(0)
{

}

PakStatInfo::~PakStatInfo()
{

}

void PakStatInfo::addOnePak()
{
	++m_pakCount;
}

void PakStatInfo::clearCurPakIdx()
{
	m_curPakIdx = 0;
}

void PakStatInfo::addCurPakIdx()
{
	++m_curPakIdx;
}

uint32 PakStatInfo::getCurPakIdx()
{
	return m_curPakIdx;
}

void PakStatInfo::addOneFile()
{
	++m_fileCount;
}

void PakStatInfo::addOneFileSize(uint32 fileSize)
{
	m_fileSize += fileSize;
}

void PakStatInfo::clear()
{
	m_pakCount = 0;
	m_curPakIdx = 0;
	m_fileCount = 0;
	m_fileSize = 0;
}

END_NAMESPACE_FILEARCHIVETOOL