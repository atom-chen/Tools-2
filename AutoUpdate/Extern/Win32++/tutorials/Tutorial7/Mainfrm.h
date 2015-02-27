///////////////////////////////////////////////////////
// Mainfrm.h
//  Declaration of the CMainFrame class

#ifndef MAINFRM_H
#define MAINFRM_H

#include "frame.h"
#include "View.h"


class CMainFrame : public CFrame
{
public:
	CMainFrame(void);
	virtual ~CMainFrame();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnFileExit();
	virtual void OnFileNew();
	virtual void OnFileOpen();
	virtual void OnFileSave();
	virtual void OnFileSaveAs();
	virtual void OnFilePrint();
	virtual void OnPenBlack();
	virtual void OnPenBlue();
	virtual void OnPenGreen();
	virtual void OnPenRed();
	virtual void SetupToolBar();
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	enum Pens
	{
		RED, BLUE, GREEN, BLACK
	};
	
	CView m_View;
};

#endif //MAINFRM_H

