#include <windows.h>
#include <stdio.h>
#include <string.h>

// 返回可执行文件所在的目录(不包含最后的'\')
void GetExePath(TCHAR* sFileName)
{
	HMODULE hMyModule = GetModuleHandle(nullptr);
	DWORD len = GetModuleFileName(hMyModule, sFileName, 255);
	int idx = len - 1;
	for (; idx >= 0; --idx)
	{
		if (sFileName[idx] == '\\')
		{
			sFileName[idx] = '\0';
			break;
		}
	}
}

typedef ULONG(*MYPROC)(void);
int main()
{
	// 加载的 dll 完整目录
	//TCHAR* dllName = "D:\\file\\opensource\\EasyOgreMaxExporter-svn\\output\\x64\\vs12\\Release Max 2015\\EasyOgreExporter.dle";
	TCHAR* dllName = "D:\\file\\opensource\\unity-game-git\\unitygame\\Tools\\3dMaxExport_KOK\\CurEasy\\build\\Easy\\Debug\\EasyOgreExporter_2015_64.dle";

	// 需要额外添加的 path 环境变量
	TCHAR* extPath = "F:\\ProgramFiles\\Autodesk\\3ds Max 2015;F:\\ProgramFiles\\Autodesk\\3ds Max 2015\\stdplugs";

	TCHAR curPath[1024] = {0};
	// 获取当前环境变量的名字
	GetEnvironmentVariable("path", curPath, 1024);
	if (strlen(curPath))
	{
		strcat(curPath, ";");
	}
	strcat(curPath, extPath);
	// 设置新的环境变量内容
	SetEnvironmentVariable("path", curPath);

	// 当前工作目录
	TCHAR chCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, chCurDir);

	// 获取 exe 所在目录
	TCHAR dllPath[MAX_PATH] = { 0 };
	GetExePath(dllPath);

	// 设置当前工作目录为 exe 所在目录
	SetCurrentDirectory(dllPath);

	// 加载 dll 
	HINSTANCE LibHandle;
	MYPROC ProcAdd;
	//LibHandle = LoadLibrary(dllName);
	LibHandle = LoadLibraryEx(dllName, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
	printf("user32 LibHandle = //x%p\n", LibHandle);
	ProcAdd = (MYPROC)GetProcAddress(LibHandle, "LibVersion");
	if (ProcAdd != nullptr)
	{
		printf("LibVersionAddress = //x%p\n", ProcAdd);
		printf("LibVersion = %ld\n", ProcAdd());
	}
	SetCurrentDirectory(chCurDir);

	return 0;
}