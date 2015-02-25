#ifndef __QtFileArchiveToolSys_H_
#define __QtFileArchiveToolSys_H_

#include "FileArchiveToolSys.h"

class QtFileArchiveToolSys : public FileArchiveToolSys
{
public:
	QtFileArchiveToolSys();

	// 这里写是为了解决链接错误
protected:
	static QtFileArchiveToolSys* m_sSingleton;

public:
	static QtFileArchiveToolSys* getSingletonPtr();
};

#endif		// __QTAIEDITORSYS_H_