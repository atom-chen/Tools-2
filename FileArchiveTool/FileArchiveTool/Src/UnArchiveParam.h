#ifndef __UnArchiveParam_H
#define __UnArchiveParam_H

#include "Prerequisites.h"
#include "PakParam.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT UnArchiveParam : public PakParam
{
protected:
	char* m_punArchiveFilePath;
	//char* m_punArchiveOutDir;

public:
	UnArchiveParam(EPakParam ePakParam = ePP_UnPak);
	virtual ~UnArchiveParam();

	void setUnArchiveFilePath(const char* pPath);
	//void setUnArchiveOutDir(const char* pPath);

	const char* getUnArchiveFilePath();
	//const char* getUnArchiveOutDir();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif