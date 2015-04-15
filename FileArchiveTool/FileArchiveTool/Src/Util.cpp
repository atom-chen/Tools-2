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

//�ݹ���г��ļ��������е����ļ��к��ļ�
//���� path: Ҫ���в��ҵ�Ŀ¼·��
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t���ļ���Ϣ�ṹ��    
	long Handle;
	char tempdir[MAX_PATH] = { 0 }; //����һ����ʱ�ַ�����
	strcat(tempdir, walkPath); //�����ַ���
	strcat(tempdir, "/*.*"); //�����ַ���(������RAR��β���ļ�)
	Handle = _findfirst(tempdir, &FileInfo); //��ʼ�����ļ�

	if (Handle == -1L) //����Ŀ¼�з����������ļ�
	{
		//printf("û���ҵ�\n");	// һ���ļ���û���ҵ�
	}
	else
	{
		// �����ҵ����ǵ�ǰ�ļ���"."�����Բ��ô���
		int ret = _findnext(Handle, &FileInfo);
		while (ret != -1)
		{
			if ((FileInfo.attrib & _A_SUBDIR) == 16 && 
				strcmp(FileInfo.name, "...") != 0 && 
				strcmp(FileInfo.name, "..") != 0 && 
				strcmp(FileInfo.name, ".") != 0)	// ��Ŀ¼
			{
				memset(tempdir, 0, MAX_PATH);
				strcat(tempdir, walkPath); //�����ַ���
				strcat(tempdir, "/"); //�����ַ���
				strcat(tempdir, FileInfo.name); //�����ַ���(������RAR��β���ļ�)
				walkDir(tempdir);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR) &&
				strcmp(FileInfo.name, "...") != 0 &&
				strcmp(FileInfo.name, "..") != 0 &&
				strcmp(FileInfo.name, ".") != 0)				// �ļ�
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
		if ((_access(strPath, 0)) == -1)		// Ŀ¼������
		{
			_mkdir(strPath);
		}
		startPos = pPos + 1;
	}

	// ��������Ŀ¼
	if ((_access(m_pPath, 0)) == -1)		// Ŀ¼������
	{
		_mkdir(m_pPath);
	}
}

// �ַ����滻����.
// ���滻���е�Ҫ�滻���ַ���,���滻���ַ������滻���ַ�����һ��һ����.
// pInput - �����ַ���.
// pOutput - ����ַ���, Ҫ��֤�㹻�Ŀռ���Դ洢�滻����ַ���.
// pSrc - Ҫ���滻�����ַ���, ����%user%
// pDst - Ҫ�滻�ɵ��ַ���, ����user1
// ע��:���ϵ��ַ�����Ҫ��'\0'��β.
//
void Util::Substitute(char *pInput, char *pOutput, char *pSrc, char *pDst)
{
	char *pi, *po, *p;
	int nSrcLen, nDstLen, nLen;

	// ָ�������ַ������ζ�ָ��.
	pi = pInput;
	// ָ������ַ������ζ�ָ��.
	po = pOutput;
	// ���㱻�滻�����滻���ĳ���.
	nSrcLen = strlen(pSrc);
	nDstLen = strlen(pDst);

	// ����piָ���ַ����е�һ�γ����滻����λ��,������ָ��(�Ҳ����򷵻�null).  
	p = strstr(pi, pSrc);
	if (p)
	{
		// �ҵ�.
		while (p)
		{
			// ���㱻�滻��ǰ���ַ����ĳ���.
			nLen = (int)(p - pi);
			// ���Ƶ�����ַ���.
			memcpy(po, pi, nLen);
			memcpy(po + nLen, pDst, nDstLen);
			// �������滻��.
			pi = p + nSrcLen;
			// ����ָ���������ָ��λ��.
			po = po + nLen + nDstLen;
			// ��������.
			p = strstr(pi, pSrc);
		}
		// ����ʣ���ַ���.
		strcpy(po, pi);
	}
	else
	{
		// û���ҵ���ԭ������.
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

//ע�⣺���ַ���Ϊ��ʱ��Ҳ�᷵��һ�����ַ���  
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