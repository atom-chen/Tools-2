#include "Util.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

//�ݹ���г��ļ��������е����ļ��к��ļ�
//���� path: Ҫ���в��ҵ�Ŀ¼·��
void Util::walkDir(const char* walkPath)
{
	struct _finddata_t FileInfo; //_finddata_t���ļ���Ϣ�ṹ��    
	long Handle;
	if ((Handle = _findfirst(walkPath, &FileInfo)) == -1L) //����Ŀ¼�з����������ļ�
	{
		//printf("û���ҵ�\n");	// һ���ļ���û���ҵ�
	}
	else
	{
		// �����ҵ����ǵ�ǰ�ļ���"."�����Բ��ô���    
		while (!_findnext(Handle, &FileInfo))
		{
			if ((FileInfo.attrib & _A_SUBDIR) == 16 && strcmp(FileInfo.name, ".."))	// ��Ŀ¼
			{
				//printf("���ļ��У�%s\n", FileInfo.name);
				walkDir(FileInfo.name);
			}
			else if (!(FileInfo.attrib & _A_SUBDIR))				// �ļ�
			{
				//printf("�ļ�:%s\n", FileInfo.name);
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