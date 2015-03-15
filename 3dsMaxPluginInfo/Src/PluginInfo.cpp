#include <windows.h>
#include <stdio.h>
#include <string.h>

// ���ؿ�ִ���ļ����ڵ�Ŀ¼(����������'\')
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
	// ���ص� dll ����Ŀ¼
	//TCHAR* dllName = "D:\\file\\opensource\\EasyOgreMaxExporter-svn\\output\\x64\\vs12\\Release Max 2015\\EasyOgreExporter.dle";
	TCHAR* dllName = "D:\\file\\opensource\\unity-game-git\\unitygame\\Tools\\3dMaxExport_KOK\\CurEasy\\build\\Easy\\Debug\\EasyOgreExporter_2015_64.dle";

	// ��Ҫ������ӵ� path ��������
	TCHAR* extPath = "F:\\ProgramFiles\\Autodesk\\3ds Max 2015;F:\\ProgramFiles\\Autodesk\\3ds Max 2015\\stdplugs";

	TCHAR curPath[1024] = {0};
	// ��ȡ��ǰ��������������
	GetEnvironmentVariable("path", curPath, 1024);
	if (strlen(curPath))
	{
		strcat(curPath, ";");
	}
	strcat(curPath, extPath);
	// �����µĻ�����������
	SetEnvironmentVariable("path", curPath);

	// ��ǰ����Ŀ¼
	TCHAR chCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, chCurDir);

	// ��ȡ exe ����Ŀ¼
	TCHAR dllPath[MAX_PATH] = { 0 };
	GetExePath(dllPath);

	// ���õ�ǰ����Ŀ¼Ϊ exe ����Ŀ¼
	SetCurrentDirectory(dllPath);

	// ���� dll 
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