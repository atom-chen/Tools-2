#ifdef WIN32
#include <windows.h>		// ��ʱ���� windows �Լ���ת������
#endif

#include "CharsetConv.h"
#include "iconv.h"
#include <string.h>

BEGIN_NAMESPACE_FILEARCHIVETOOL

CharsetConv::CharsetConv()
{
	m_bytes = new char[4096];
}

CharsetConv::~CharsetConv()
{
	delete[]m_bytes;
}

int CharsetConv::convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	//iconv_t cd;
	//const char **pin = (const char **)&inbuf;
	//char **pout = &outbuf;

	//cd = iconv_open(to_charset, from_charset);
	//if (cd == 0) return -1;
	//memset(outbuf, 0, outlen);
	//if (iconv(cd, pin, (size_t*)&inlen, pout, (size_t*)&outlen) == -1) return -1;
	//iconv_close(cd);
	return 0;
}

// utf-8 ��תΪ���� GB2312 ����
int CharsetConv::utf2Local(char *inbuf, int inlen, char *outbuf, int outlen)
{
	return convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
// ���� GB2312 ����תΪ utf-8 ����
int CharsetConv::local2Utf(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

// ȫ�ֺ�����ʹ�� windows �������
// GBK ����ת����UTF8����
int CharsetConv::LocalToUtf8(char * lpGBKStr, char * lpUTF8Str, int nUTF8StrLen)
{
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpGBKStr)  //���GBK�ַ���ΪNULL������˳�
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char *)lpGBKStr, -1, NULL, NULL);  //��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //ΪUnicode�ַ����ռ�
	nRetLen = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char *)lpGBKStr, -1, lpUnicodeStr, nRetLen);  //ת����Unicode����
	if (!nRetLen)  //ת��ʧ��������˳�
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  //��ȡת����UTF8���������Ҫ���ַ��ռ䳤��

	if (!lpUTF8Str)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nUTF8StrLen < nRetLen)  //���������������Ȳ������˳�
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *)lpUTF8Str, nUTF8StrLen, NULL, NULL);  //ת����UTF8����

	if (lpUnicodeStr)
		delete[]lpUnicodeStr;

	return nRetLen;
}

// UTF8����ת����GBK����
int CharsetConv::Utf8ToLocal(char * lpUTF8Str, char * lpGBKStr, int nGBKStrLen)
{
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = 0;

	if (!lpUTF8Str)  //���UTF8�ַ���ΪNULL������˳�
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, lpUTF8Str, -1, NULL, NULL);  //��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
	lpUnicodeStr = new WCHAR[nRetLen + 1];  //ΪUnicode�ַ����ռ�
	nRetLen = ::MultiByteToWideChar(CP_UTF8, 0, lpUTF8Str, -1, lpUnicodeStr, nRetLen);  //ת����Unicode����
	if (!nRetLen)  //ת��ʧ��������˳�
		return 0;

	nRetLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicodeStr, -1, NULL, NULL, NULL, NULL);  //��ȡת����GBK���������Ҫ���ַ��ռ䳤��

	if (!lpGBKStr)  //���������Ϊ���򷵻�ת������Ҫ�Ŀռ��С
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return nRetLen;
	}

	if (nGBKStrLen < nRetLen)  //���������������Ȳ������˳�
	{
		if (lpUnicodeStr)
			delete[]lpUnicodeStr;
		return 0;
	}

	nRetLen = ::WideCharToMultiByte(CP_ACP, 0, lpUnicodeStr, -1, lpGBKStr, nRetLen, NULL, NULL);  //ת����GBK����

	if (lpUnicodeStr)
		delete[]lpUnicodeStr;

	return nRetLen;
}

char* CharsetConv::Utf8ToLocalStr(char * lpUTF8Str)
{
	memset(m_bytes, 0, 4096);
	Utf8ToLocal(lpUTF8Str, m_bytes, 4096);

	return m_bytes;
}

char* CharsetConv::LocalToUtf8Str(char * lpGBKStr)
{
	memset(m_bytes, 0, 4096);
	LocalToUtf8(lpGBKStr, m_bytes, 4096);

	return m_bytes;
}

int CharsetConv::Utf8ToLocalStrLen(char * lpUTF8Str)
{
	return Utf8ToLocal(lpUTF8Str, nullptr, 4096);
}

int CharsetConv::LocalToUtf8StrLen(char * lpGBKStr)
{
	return LocalToUtf8(lpGBKStr, nullptr, 4096);
}

END_NAMESPACE_FILEARCHIVETOOL