#ifndef __FileArchiveToolSys_H_
#define __FileArchiveToolSys_H_

#include "Singleton.h"
#include "Platform.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class Config;

class FILEARCHIVETOOL_EXPORT FileArchiveToolSys : public Singleton<FileArchiveToolSys>
{
protected:
	Config* m_pConfig;		// ª˘±æ≈‰÷√

public:
	FileArchiveToolSys();
	virtual ~FileArchiveToolSys();

public:
	Config* getConfigPtr();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif