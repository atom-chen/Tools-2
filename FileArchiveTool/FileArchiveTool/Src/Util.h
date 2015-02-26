#ifndef __Util_H
#define __Util_H

#include <io.h>
#include "Prerequisites.h"
#include "FastDelegate.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT Util
{
	typedef fastdelegate::FastDelegate2<const char*, _finddata_t*, bool> WalkDirDelegate;

protected:
	WalkDirDelegate* m_walkDirDelegate;
	char* m_pPath;

public:
	Util();
	~Util();

public:
	//void bindWalkDirDelegate(WalkDirDelegate dirDelegate);
	WalkDirDelegate* getWalkDirDelegatePtr();
	void walkDir(const char* walkPath);

	const char* getFullPathNoFileName(const char* filePath);	// ��ȡ�ļ�����Ŀ¼�������ļ�����Ŀ¼������
	const char* getFullPathNoExtName(const char* filePath);
	const char* getLastPathName(const char* filePath);	// ��ȡ�ļ�����Ŀ¼���һ������
	void mkDir(const char* dir);		// �������Ŀ¼
	void Substitute(char *pInput, char *pOutput, char *pSrc, char *pDst);
	void normPath(char *pPath);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif