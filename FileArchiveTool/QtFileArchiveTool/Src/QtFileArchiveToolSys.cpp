#include "QtFileArchiveToolSys.h"

QtFileArchiveToolSys* QtFileArchiveToolSys::m_sSingleton = 0;

QtFileArchiveToolSys::QtFileArchiveToolSys()
{
	
}

QtFileArchiveToolSys* QtFileArchiveToolSys::getSingletonPtr()
{
	if (m_sSingleton == nullptr)
	{
		m_sSingleton = new QtFileArchiveToolSys();
	}
	return m_sSingleton;
}
