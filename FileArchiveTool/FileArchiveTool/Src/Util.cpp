#include "Util.h"
#include <string.h>
#include <io.h>
#include <direct.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

Util::Util()
{
	m_walkDirDelegate = new WalkDirDelegate();
	m_pPath = new char[MAX_PATH];
}

Util::~Util()
{
	delete m_walkDirDelegate;
	delete []m_pPath;
}

//递归的列出文件夹下所有的子文件夹和文件
//参数 path: 要进行查找的目录路径
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t是文件信息结构体    
	long Handle;
	char tempdir[MAX_PATH] = { 0 }; //定义一个临时字符数组
	strcat(tempdir, walkPath); //连接字符串
	strcat(tempdir, "/*.*"); //连接字符串(搜索以RAR结尾的文件)
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
				memset(tempdir, 0, MAX_PATH);
				strcat(tempdir, walkPath); //连接字符串
				strcat(tempdir, "/"); //连接字符串
				strcat(tempdir, FileInfo.name); //连接字符串(搜索以RAR结尾的文件)
				walkDir(tempdir);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR) &&
				strcmp(FileInfo.name, "...") != 0 &&
				strcmp(FileInfo.name, "..") != 0 &&
				strcmp(FileInfo.name, ".") != 0)				// 文件
			{
				if (m_walkDirDelegate != nullptr && (*m_walkDirDelegate))
				{
					(*m_walkDirDelegate)(walkPath, &FileInfo);
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

const char* Util::getFullPathNoFileName(const char* filePath)
{
	normPath((char*)filePath);
	memset(m_pPath, 0, MAX_PATH);
	const char * pPos = strrchr(filePath, '/');
	if (pPos != nullptr)
	{
		strncpy(m_pPath, filePath, (pPos - filePath));
	}

	return m_pPath;
}

const char* Util::getFullPathNoExtName(const char* filePath)
{
	normPath((char*)filePath);
	memset(m_pPath, 0, MAX_PATH);
	const char * pPos = strrchr(filePath, '.');
	if (pPos != nullptr)
	{
		strncpy(m_pPath, filePath, (pPos - filePath));
	}

	return m_pPath;
}

const char* Util::getLastPathName(const char* filePath)
{
	normPath((char*)filePath);
	memset(m_pPath, 0, MAX_PATH);
	const char * pPos = strrchr(filePath, '/');
	if (pPos != nullptr)
	{
		pPos += 1;
		strncpy(m_pPath, pPos, strlen(filePath) - (pPos - filePath));
	}

	return m_pPath;
}

void Util::mkDir(const char* dir)
{
	char* strPath = new char[MAX_PATH];
	memset(strPath, 0, MAX_PATH);
	Substitute((char*)dir, m_pPath, "\\", "/");

	const char * startPos = m_pPath;
	const char * pPos;
	while ((pPos = strchr(startPos, '/')) != nullptr)
	{
		strncpy(strPath, m_pPath, pPos - m_pPath);
		if ((_access(strPath, 0)) == -1)		// 目录不存在
		{
			_mkdir(strPath);
		}
		startPos = pPos + 1;
	}

	// 创建最后的目录
	if ((_access(m_pPath, 0)) == -1)		// 目录不存在
	{
		_mkdir(m_pPath);
	}
}

// 字符串替换函数.
// 能替换所有的要替换的字符串,被替换的字符串和替换的字符串不一定一样长.
// pInput - 输入字符串.
// pOutput - 输出字符串, 要保证足够的空间可以存储替换后的字符串.
// pSrc - 要被替换的子字符串, 比如%user%
// pDst - 要替换成的字符串, 比如user1
// 注意:以上的字符串均要以'\0'结尾.
//
void Util::Substitute(char *pInput, char *pOutput, char *pSrc, char *pDst)
{
	char *pi, *po, *p;
	int nSrcLen, nDstLen, nLen;

	// 指向输入字符串的游动指针.
	pi = pInput;
	// 指向输出字符串的游动指针.
	po = pOutput;
	// 计算被替换串和替换串的长度.
	nSrcLen = strlen(pSrc);
	nDstLen = strlen(pDst);

	// 查找pi指向字符串中第一次出现替换串的位置,并返回指针(找不到则返回null).  
	p = strstr(pi, pSrc);
	if (p)
	{
		// 找到.
		while (p)
		{
			// 计算被替换串前边字符串的长度.
			nLen = (int)(p - pi);
			// 复制到输出字符串.
			memcpy(po, pi, nLen);
			memcpy(po + nLen, pDst, nDstLen);
			// 跳过被替换串.
			pi = p + nSrcLen;
			// 调整指向输出串的指针位置.
			po = po + nLen + nDstLen;
			// 继续查找.
			p = strstr(pi, pSrc);
		}
		// 复制剩余字符串.
		strcpy(po, pi);
	}
	else
	{
		// 没有找到则原样复制.
		strcpy(po, pi);
	}
}

void Util::normPath(char *pPath)
{
	int idx = 0;
	for (; idx < strlen(pPath); ++idx)
	{
		if (pPath[idx] == '\\')
		{
			pPath[idx] = '/';
		}
	}
}

void Util::trim_right(std::string& str)
{
	boost::trim_right(str);
}

//注意：当字符串为空时，也会返回一个空字符串  
void Util::split(std::string& s, std::string& delim, std::vector< std::string >& ret)
{
	size_t last = 0;
	size_t index = std::string::npos;
	while ((index = s.find_first_of(delim, last)) != std::string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + delim.length();
	}

	if (s.length() > last)
	{
		ret.push_back(s.substr(last, s.length() - last));
	}
}

END_NAMESPACE_FILEARCHIVETOOL