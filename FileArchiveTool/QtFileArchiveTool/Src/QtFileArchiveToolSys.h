#ifndef __QtFileArchiveToolSys_H_
#define __QtFileArchiveToolSys_H_

#include "FileArchiveToolSys.h"

class QtFileArchiveToolSys : public FileArchiveToolSys
{
public:
	QtFileArchiveToolSys();

	// ����д��Ϊ�˽�����Ӵ���
protected:
	static QtFileArchiveToolSys* m_sSingleton;

public:
	static QtFileArchiveToolSys* getSingletonPtr();
};

#endif		// __QTAIEDITORSYS_H_