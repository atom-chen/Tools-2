#ifndef __CharsetConv_H
#define __CharsetConv_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

class FILEARCHIVETOOL_EXPORT CharsetConv
{
protected:
	char* m_bytes;

public:
	CharsetConv();
	~CharsetConv();

public:
	int convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
	int utf2Local(char *inbuf, int inlen, char *outbuf, int outlen);
	int local2Utf(char *inbuf, size_t inlen, char *outbuf, size_t outlen);
	char* Utf8ToLocalStr(char * lpUTF8Str);
	char* LocalToUtf8Str(char * lpGBKStr);

	int Utf8ToLocalStrLen(char * lpUTF8Str);		// �����ǻ�ȡת������ַ����ĳ���
	int LocalToUtf8StrLen(char * lpGBKStr);			// �����ǻ�ȡת������ַ����ĳ���

protected:
	int LocalToUtf8(char * lpGBKStr, char * lpUTF8Str, int nUTF8StrLen);
	int Utf8ToLocal(char * lpUTF8Str, char * lpGBKStr, int nGBKStrLen);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif