#include "FileArchiveToolSys.h"
#include "Config.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

template <> FileArchiveToolSys* Singleton<FileArchiveToolSys>::m_sSingleton = 0;

FileArchiveToolSys::FileArchiveToolSys()
{
	m_pConfig = new Config();
}

FileArchiveToolSys::~FileArchiveToolSys()
{

}

Config* FileArchiveToolSys::getConfigPtr()
{
	return m_pConfig;
}

END_NAMESPACE_FILEARCHIVETOOL