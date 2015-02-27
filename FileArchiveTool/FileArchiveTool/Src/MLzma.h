#ifndef __MLzma_H
#define __MLzma_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 * @brief ִ�� LZMA ѹ��
 */
class FILEARCHIVETOOL_EXPORT MLzma
{
public:
	MLzma();
	~MLzma();

	bool LzmaFileCompress(const char*scrfilename, const char*desfilename);			// �ļ�ѹ��
	bool LzmaFileUncompress(const char*scrfilename, const char*desfilename);		// �ļ���ѹ��

	bool LzmaStrCompress(const char*scrStr, char*desStr);					// �ַ���ѹ��
	bool LzmaStrUncompress(const char*scrStr, char*desStr);				// �ַ�����ѹ��
};

END_NAMESPACE_FILEARCHIVETOOL

#endif