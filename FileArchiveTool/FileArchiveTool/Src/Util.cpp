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

//�ݹ���г��ļ��������е����ļ��к��ļ�
//���� path: Ҫ���в��ҵ�Ŀ¼·��
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t���ļ���Ϣ�ṹ��    
	long Handle;
	char tempdir[256] = { 0 }; //����һ����ʱ�ַ�����
	strcat(tempdir, walkPath); //�����ַ���
	strcat(tempdir, "\\*.*"); //�����ַ���(������RAR��β���ļ�)
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
				walkDir(FileInfo.name);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR) &&
				strcmp(FileInfo.name, "...") != 0 &&
				strcmp(FileInfo.name, "..") != 0 &&
				strcmp(FileInfo.name, ".") != 0)				// �ļ�
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