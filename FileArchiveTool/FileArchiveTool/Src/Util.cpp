#include "Util.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

//递归的列出文件夹下所有的子文件夹和文件
//参数 path: 要进行查找的目录路径
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t是文件信息结构体    
	long Handle;
	if ((Handle = _findfirst(walkPath, &FileInfo)) == -1L) //查找目录中符合条件的文件
	{
		//printf("没有找到\n");	// 一个文件都没有找到
	}
	else
	{
		// 最先找到的是当前文件夹"."，所以不用处理    
		while (!_findnext(Handle, &FileInfo))
		{
			if ((FileInfo.attrib & _A_SUBDIR) == 16 && strcmp(FileInfo.name, ".."))	// 子目录
			{
				//printf("子文件夹：%s\n", FileInfo.name);
				walkDir(FileInfo.name);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR))				// 文件
			{
				//printf("文件:%s\n", FileInfo.name);
				if (m_walkDirDelegate)
				{
					m_walkDirDelegate(&FileInfo);
				}
			}
		}
		_findclose(Handle);
	}
}

void Util::bindWalkDirDelegate(WalkDirDelegate dirDelegate)
{
	m_walkDirDelegate = dirDelegate;
}

END_NAMESPACE_FILEARCHIVETOOL