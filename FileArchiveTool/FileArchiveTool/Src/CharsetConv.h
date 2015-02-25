#ifndef __CharsetConv_H
#define __CharsetConv_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT CharsetConv
{
public:
	static int convert(const char *from, const char *to, char* save, int savelen, char *src, int srclen);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif