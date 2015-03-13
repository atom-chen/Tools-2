#include "AppFrame.h"
#include "MImport3dMax.h"

AppFrame::AppFrame()
{
	m_ProgOptions = new ProgOptions;
	m_pMImport3dMax = new MImport3dMax;
}

AppFrame::~AppFrame()
{

}

void AppFrame::init(int argc, char *argv[])
{
	
}

void AppFrame::run()
{
	m_pMImport3dMax->import("");
}

void AppFrame::stop()
{

}