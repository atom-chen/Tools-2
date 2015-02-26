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

	const char* getFullPathNoFileName(const char* filePath);	// 获取文件或则目录不包括文件或者目录的名字
	const char* getFullPathNoExtName(const char* filePath);
	const char* getLastPathName(const char* filePath);	// 获取文件或则目录最后一个名字
	void mkDir(const char* dir);		// 创建这个目录
	void Substitute(char *pInput, char *pOutput, char *pSrc, char *pDst);
	void normPath(char *pPath);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif