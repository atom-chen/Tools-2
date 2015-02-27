#ifndef __MLzma_H
#define __MLzma_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define LZMA_HEADER_LEN 13

/**
 * @brief ִ�� LZMA ѹ��
 */
class FILEARCHIVETOOL_EXPORT MLzma
{
public:
	MLzma();
	~MLzma();

	static bool LzmaFileCompress(const char* scrfilename, const char* desfilename);			// �ļ�ѹ��
	static bool LzmaFileUncompress(const char* scrfilename, const char* desfilename);		// �ļ���ѹ��

	static bool LzmaStrCompress(const char* scrStr, char** desStr, uint32* len = nullptr);					// �ַ���ѹ��
	static bool LzmaStrUncompress(const char* scrStr, char** desStr, uint32* len = nullptr);				// �ַ�����ѹ��
};

END_NAMESPACE_FILEARCHIVETOOL

#endif