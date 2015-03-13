#ifndef __MExportSkeleton_H_
#define __MExportSkeleton_H_

#include <string>

class AWD;

class MExportSkeleton
{
public:
	void exportSkeleton(std::string fullPath, AWD* pAwd);
};

#endif