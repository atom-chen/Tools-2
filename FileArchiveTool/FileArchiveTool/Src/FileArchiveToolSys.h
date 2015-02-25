#ifndef __FileArchiveToolSys_H_
#define __FileArchiveToolSys_H_

#include "Prerequisites.h"
#include "Singleton.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class Config;
class ArchiveData;
class CharsetConv;

class FILEARCHIVETOOL_EXPORT FileArchiveToolSys : public Singleton<FileArchiveToolSys>
{
protected:
	Config* m_pConfig;		// ª˘±æ≈‰÷√
	ArchiveData* m_pArchiveData;
	CharsetConv* m_pCharsetConv;

public:
	FileArchiveToolSys();
	virtual ~FileArchiveToolSys();

public:
	Config* getConfigPtr();
	ArchiveData* getArchiveDataPtr();
	CharsetConv* getCharsetConvPtr();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif