#ifndef __PakStatInfo_H
#define __PakStatInfo_H

/**
* @brief ����һ��ͳ�ư�����Ϣ����
*/
#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT PakStatInfo
{
protected:
	uint32 m_pakCount;			// ��������
	uint32 m_curPakIdx;			// ��ǰ������������ 0 ��ʼ
	uint32 m_fileCount;			// �ļ��ܹ�����
	uint32 m_fileSize;			// �ļ��ܹ���С

public:
	PakStatInfo();
	~PakStatInfo();

	// ���һ��
	void addOnePak();
	void clearCurPakIdx();
	void addCurPakIdx();
	uint32 getCurPakIdx();
	void addOneFile();
	void addOneFileSize(uint32 fileSize);

	void clear();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif