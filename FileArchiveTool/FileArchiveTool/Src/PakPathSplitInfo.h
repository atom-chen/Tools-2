#ifndef __PakPathSplitInfo_H
#define __PakPathSplitInfo_H

/**
* @brief ����һ��Ŀ¼��ʱ�򣬽�Ŀ¼�ֲ���Լ���Ҫ����Ϣ��Ȼ����д���
*/
#include "Prerequisites.h"

#include <string>
#include <stddef.h>
#include <io.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT PakPathSplitInfo
{
protected:
	std::string* m_origPath;	// ԭʼ��Ŀ¼
	std::string* m_pakName;		// �������֣�����ǵ����İ������֣������ܼ������
	std::string* m_pakFilePath;	// ����ǰ����ļ���Ŀ¼�������ڰ��У����ص�ʱ��ʹ��
	std::string* m_origFileName;	// ԭʼ�ļ�������
	std::size_t m_fileOrigSize;			// �ļ�ԭʼ��С
	std::size_t m_fileCompressSize;		// �ļ�ѹ����Ĵ�С

public:
	PakPathSplitInfo();
	~PakPathSplitInfo();

	/**
	 * @brief path ��������·��
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