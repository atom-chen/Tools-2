#ifndef __UnArchiveParam_H
#define __UnArchiveParam_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT UnArchiveParam
{
protected:
	char* m_punArchiveFilePath;
	char* m_punArchiveOutDir;

public:
	UnArchiveParam();
	~UnArchiveParam();

	void setUnArchiveFilePath(const char* pPath);
	void setUnArchiveOutDir(const char* pPath);

	const char* getUnArchiveFilePath();
	const char* getUnArchiveOutDir();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif