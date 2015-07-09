#ifndef __UtilEncode_H
#define __UtilEncode_H

#include "QtIncAll.h"

class UtilEncode
{
public:
	static QString local2Unicode(QString src);
	static QString unicode2Local(QString src);
};

#endif