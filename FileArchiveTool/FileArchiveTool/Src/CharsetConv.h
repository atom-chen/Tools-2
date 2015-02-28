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
	//int convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen);
	int convert(const char* toConverterName, const char* fromConverterName, char* target, int32 targetCapacity, const char* source, int32 sourceLength);
	char* Utf8ToLocalStr(char * lpUTF8Str);
	char* LocalToUtf8Str(char * lpGBKStr);

	int Utf8ToLocalStrLen(char * lpUTF8Str);		// �����ǻ�ȡת������ַ����ĳ��ȣ����صĳ�������Ҫ�ĳ��� + 1��ע���� + 1
	int LocalToUtf8StrLen(char * lpGBKStr);

protected:
	int LocalToUtf8(char * lpGBKStr, char * lpUTF8Str, int nUTF8StrLen);
	int Utf8ToLocal(char * lpUTF8Str, char * lpGBKStr, int nGBKStrLen);
};

END_NAMESPACE_FILEARCHIVETOOL

#endif