#ifndef __MLzma_H
#define __MLzma_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define LZMA_HEADER_LEN 13

/**
 * @brief Ö´ÐÐ LZMA Ñ¹Ëõ
 */
class FILEARCHIVETOOL_EXPORT MLzma
{
public:
	MLzma();
	~MLzma();

	static bool LzmaFileCompress(const char* scrfilename, const char* desfilename);			// ÎÄ¼þÑ¹Ëõ
	static bool LzmaFileUncompress(const char* scrfilename, const char* desfilename);		// ÎÄ¼þ½âÑ¹Ëõ

	static bool LzmaStrCompress(const char* scrStr, uint32 srcLen, char** desStr, uint32* destLen = nullptr);					// ×Ö·û´®Ñ¹Ëõ
	static bool LzmaStrUncompress(const char* scrStr, uint32 srcLen, char** desStr, uint32* destLen = nullptr);				// ×Ö·û´®½âÑ¹Ëõ
};

END_NAMESPACE_FILEARCHIVETOOL

#endif