#ifndef __QtFileArchiveToolSys_H_
#define __QtFileArchiveToolSys_H_

#include "FileArchiveTool.h"

class QtFileArchiveToolSys : public FileArchiveToolSys
{
public:
	QtFileArchiveToolSys();
	virtual ~QtFileArchiveToolSys();

	virtual void init();	// ���캯�������������������
	virtual void destroy();	// �������ͷ�������Դ
};

#define QtFileArchiveToolSysDef QtFileArchiveToolSys::getSingletonPtr()

#endif		// __QTAIEDITORSYS_H_