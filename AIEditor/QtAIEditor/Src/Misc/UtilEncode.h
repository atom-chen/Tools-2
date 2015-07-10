#ifndef __UtilEncode_H
#define __UtilEncode_H

#include "QtIncAll.h"
#include <string>

class UtilEncode
{
public:
	static QString qLocal2QUnicode(QString src);
	static QString qUnicode2QLocal(QString src);

	static QString sLocal2QUnicode(std::string src);
	static std::string qUnicode2SLocal(QString src);
};

#endif