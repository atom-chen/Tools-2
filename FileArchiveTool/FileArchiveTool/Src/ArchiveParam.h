#ifndef __ArchiveParam_H
#define __ArchiveParam_H

#include "Prerequisites.h"
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define PAKEXT ".abc"

// 当前只支持打包子目录
enum FILEARCHIVETOOL_EXPORT ArchiveMode
{
	eArchiveMode_Dir,		// 打包当前目录，将当前目录下的所有的内容打包到一个文件里，可以拆包
	eArchiveMode_SubDir,	// 打包当前目录下的子目录，当前目录下的一级文件不打包，直接拷贝，可以拆包
};

class FILEARCHIVETOOL_EXPORT ArchiveParam
{
protected:
	char* m_pArchiveDir;			// Archive 目录
	char* m_pArchiveFilePath;		// Archive 输出文件名字
	ArchiveMode m_eArchiveMode;		// 打包模式

public:
	ArchiveParam();
	~ArchiveParam();

	void setArchiveDir(const char* pPath);
	void setArchiveFilePath(const char* pPath);

	const char* getArchiveDir();
	const char* getArchiveFilePath();
	bool isEqualArchiveDir(std::string& path);			// 判断目录是否与当前 ArchiveDir 相同
	void setArchiveMode(ArchiveMode mode);
	ArchiveMode getArchiveMode();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif