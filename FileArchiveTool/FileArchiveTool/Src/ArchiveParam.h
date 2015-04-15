#ifndef __ArchiveParam_H
#define __ArchiveParam_H

#include "Prerequisites.h"
#include <string>

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define PAKEXT ".abc"

// ��ǰֻ֧�ִ����Ŀ¼
enum FILEARCHIVETOOL_EXPORT ArchiveMode
{
	eArchiveMode_Dir,		// �����ǰĿ¼������ǰĿ¼�µ����е����ݴ����һ���ļ�����Բ��
	eArchiveMode_SubDir,	// �����ǰĿ¼�µ���Ŀ¼����ǰĿ¼�µ�һ���ļ��������ֱ�ӿ��������Բ��
};

class FILEARCHIVETOOL_EXPORT ArchiveParam
{
protected:
	char* m_pArchiveDir;			// Archive Ŀ¼
	char* m_pArchiveFilePath;		// Archive ����ļ�����
	ArchiveMode m_eArchiveMode;		// ���ģʽ

public:
	ArchiveParam();
	~ArchiveParam();

	void setArchiveDir(const char* pPath);
	void setArchiveFilePath(const char* pPath);

	const char* getArchiveDir();
	const char* getArchiveFilePath();
	bool isEqualArchiveDir(std::string& path);			// �ж�Ŀ¼�Ƿ��뵱ǰ ArchiveDir ��ͬ
	void setArchiveMode(ArchiveMode mode);
	ArchiveMode getArchiveMode();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif