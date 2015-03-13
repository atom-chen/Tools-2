#ifndef __AppFrame_H
#define __AppFrame_H

class MImport3dMax;
class ProgOptions;

class AppFrame
{
protected:
	ProgOptions* m_ProgOptions;
	MImport3dMax* m_pMImport3dMax;

public:
	AppFrame();
	~AppFrame();

	void init(int argc, char *argv[]);
	void run();
	void stop();
};

extern AppFrame* g_pAppFrame;

#endif