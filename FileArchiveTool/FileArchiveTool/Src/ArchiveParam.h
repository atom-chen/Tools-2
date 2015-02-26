#ifndef __ArchiveParam_H
#define __ArchiveParam_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT ArchiveParam
{
protected:
	char* m_pArchiveDir;			// Archive Ŀ¼
	char* m_pArchiveFilePath;		// Archive ����ļ�����

public:
	ArchiveParam();
	~ArchiveParam();

	void setArchiveDir(const char* pPath);
	void setArchiveFilePath(const char* pPath);

	const char* getArchiveDir();
	const char* getArchiveFilePath();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif