#include "AppFrame.h"
#include "ProgOptions.h"

AppFrame* g_pAppFrame = new AppFrame;

DEFINE_SET_GET_PFUNC(AppFrame,ProgOptions,pProgOptions);

AppFrame::AppFrame()
{
	m_pProgOptions = new ProgOptions;
}

AppFrame::~AppFrame()
{

}

void AppFrame::init(int argc, char *argv[])
{
	m_pProgOptions->parseParam(argc, argv);
}

void AppFrame::run()
{
	
}

void AppFrame::stop()
{

}