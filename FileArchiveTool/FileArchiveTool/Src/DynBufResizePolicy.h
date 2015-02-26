#ifndef __DYNBUFRESIZEPOLICY_H
#define __DYNBUFRESIZEPOLICY_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class DynBufResizePolicy
{
public:
	static uint32 getCloseSize(uint32 needSize, uint32 capacity);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif			// __DYNBUFRESIZEPOLICY_H	