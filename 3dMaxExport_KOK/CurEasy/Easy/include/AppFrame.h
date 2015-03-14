#ifndef __AppFrame_H
#define __AppFrame_H

#include "AutoDefine.h"

class ProgOptions;

class AppFrame
{
protected:
	ProgOptions* m_pProgOptions;

public:
	AppFrame();
	~AppFrame();

	void init(int argc, char *argv[]);
	void run();
	void stop();

	DECLARE_SET_GET_PFUNC(ProgOptions,pProgOptions);
};

extern AppFrame* g_pAppFrame;

#endif