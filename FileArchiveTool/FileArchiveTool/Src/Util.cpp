#include "Util.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

Util::Util()
{
	m_walkDirDelegate = new WalkDirDelegate();
}

Util::~Util()
{
	delete m_walkDirDelegate;
}

//递归的列出文件夹下所有的子文件夹和文件
//参数 path: 要进行查找的目录路径
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t是文件信息结构体    
	long Handle;
	char tempdir[256] = { 0 }; //定义一个临时字符数组
	strcat(tempdir, walkPath); //连接字符串
	strcat(tempdir, "\\*.*"); //连接字符串(搜索以RAR结尾的文件)
	Handle = _findfirst(tempdir, &FileInfo); //开始查找文件

	if (Handle == -1L) //查找目录中符合条件的文件
	{
		//printf("没有找到\n");	// 一个文件都没有找到
	}
	else
	{
		// 最先找到的是当前文件夹"."，所以不用处理
		int ret = _findnext(Handle, &FileInfo);
		while (ret != -1)
		{
			if ((FileInfo.attrib & _A_SUBDIR) == 16 && 
				strcmp(FileInfo.name, "...") != 0 && 
				strcmp(FileInfo.name, "..") != 0 && 
				strcmp(FileInfo.name, ".") != 0)	// 子目录
			{
				walkDir(FileInfo.name);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR) &&
				strcmp(FileInfo.name, "...") != 0 &&
				strcmp(FileInfo.name, "..") != 0 &&
				strcmp(FileInfo.name, ".") != 0)				// 文件
			{
				if (m_walkDirDelegate != nullptr && (*m_walkDirDelegate))
				{
					(*m_walkDirDelegate)(&FileInfo);
				}
			}
			ret = _findnext(Handle, &FileInfo);
		}
		_findclose(Handle);
	}
}

//void Util::bindWalkDirDelegate(WalkDirDelegate dirDelegate)
//{
//	m_walkDirDelegate = dirDelegate;
//}

Util::WalkDirDelegate* Util::getWalkDirDelegatePtr()
{
	return m_walkDirDelegate;
}

END_NAMESPACE_FILEARCHIVETOOL