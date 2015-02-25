#ifndef __Util_H
#define __Util_H

#include <io.h>
#include "Prerequisites.h"
#include "FastDelegate.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Util
{
	typedef fastdelegate::FastDelegate1<_finddata_t*, bool> WalkDirDelegate;

protected:
	WalkDirDelegate* m_walkDirDelegate;

public:
	Util();
	~Util();

public:
	//void bindWalkDirDelegate(WalkDirDelegate dirDelegate);
	WalkDirDelegate* getWalkDirDelegatePtr();
	void walkDir(const char* walkPath);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif