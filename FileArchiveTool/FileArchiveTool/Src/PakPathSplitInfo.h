#ifndef __PakPathSplitInfo_H
#define __PakPathSplitInfo_H

/**
* @brief 遍历一个目录的时候，将目录分拆成自己需要的信息，然后进行处理
*/
#include "Prerequisites.h"

#include <string>
#include <stddef.h>
#include <io.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT PakPathSplitInfo
{
protected:
	std::string* m_origPath;	// 原始的目录
	std::string* m_pakName;		// 包的名字，这个是导出的包的名字，最后可能加上序号
	std::string* m_pakFilePath;	// 这个是包中文件的目录，保存在包中，加载的时候使用
	std::string* m_origFileName;	// 原始文件的名字
	std::size_t m_fileOrigSize;			// 文件原始大小
	std::size_t m_fileCompressSize;		// 文件压缩后的大小

public:
	PakPathSplitInfo();
	~PakPathSplitInfo();

	/**
	 * @brief path 是完整的路径
	 */
	void initInfo(std::string& path, struct _finddata_t* FileInfo);

	std::string& getOrigPath();
	std::string& getPakName();
	std::string& getPakFilePath();
	std::string& getOrigFileName();
	std::size_t getFileOrigSize();
	std::size_t getFileCompressSize();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif