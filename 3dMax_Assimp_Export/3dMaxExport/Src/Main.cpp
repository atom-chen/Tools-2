#include "AppFrame.h"

void main(int argc, char *argv[])
{
	g_pAppFrame = new AppFrame;
	g_pAppFrame->init(argc, argv);
	g_pAppFrame->run();
	g_pAppFrame->stop();

	delete g_pAppFrame;
}