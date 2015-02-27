#ifndef __MLzma_H
#define __MLzma_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 * @brief Ö´ÐÐ LZMA Ñ¹Ëõ
 */
class FILEARCHIVETOOL_EXPORT MLzma
{
public:
	MLzma();
	~MLzma();

	bool LzmaFileCompress(const char*scrfilename, const char*desfilename);			// ÎÄ¼þÑ¹Ëõ
	bool LzmaFileUncompress(const char*scrfilename, const char*desfilename);		// ÎÄ¼þ½âÑ¹Ëõ

	bool LzmaStrCompress(const char*scrStr, char*desStr);					// ×Ö·û´®Ñ¹Ëõ
	bool LzmaStrUncompress(const char*scrStr, char*desStr);				// ×Ö·û´®½âÑ¹Ëõ
};

END_NAMESPACE_FILEARCHIVETOOL

#endif