#include "FileArchiveToolSys.h"
#include "Config.h"
#include "ArchiveData.h"
#include "CharsetConv.h"
#include "Util.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

template <> FileArchiveToolSys* Singleton<FileArchiveToolSys>::m_sSingleton = 0;

FileArchiveToolSys::FileArchiveToolSys()
{
	m_pConfig = new Config();
	m_pArchiveData = new ArchiveData();
	m_pCharsetConv = new CharsetConv();
	m_pUtil = new Util();
}

FileArchiveToolSys::~FileArchiveToolSys()
{
	delete m_pConfig;
	delete m_pArchiveData;
}

Config* FileArchiveToolSys::getConfigPtr()
{
	return m_pConfig;
}

ArchiveData* FileArchiveToolSys::getArchiveDataPtr()
{
	return m_pArchiveData;
}

CharsetConv* FileArchiveToolSys::getCharsetConvPtr()
{
	return m_pCharsetConv;
}

Util* FileArchiveToolSys::getUtilPtr()
{
	return m_pUtil;
}

END_NAMESPACE_FILEARCHIVETOOL