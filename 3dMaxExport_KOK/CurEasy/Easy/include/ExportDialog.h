#ifndef _EXPORTDIALOG_H
#define _EXPORTDIALOG_H

#include "ExPrerequisites.h"
#include "ExData.h"
#include "EasyOgreExporterLog.h"
#include "ExTools.h"
#include "tinyxml2.h"
#include "UtilWrap.h"

#include "../resources/resource.h"
#include "3dsmaxport.h"

#if defined(WIN32)
// For SHGetFolderPath.  Requires Windows XP or greater.
#include <stdarg.h>
#include <Shlobj.h>
#include <direct.h>
#endif // defined(WIN32)

namespace EasyOgreExporter
{
	INT_PTR CALLBACK IGameExporterOptionsDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	DWORD WINAPI progressCb(LPVOID arg);
}

#endif