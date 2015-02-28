extern "C" 
{
	#include "LzmaLib.h"
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLzma.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

MLzma::MLzma()
{

}

MLzma::~MLzma()
{

}

bool MLzma::LzmaFileCompress(const char* scrfilename, const char* desfilename)
{
	FILE*fin = fopen(scrfilename, "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", scrfilename);
		return false;
	}

	FILE*fout = fopen(desfilename, "wb");
	if (fout == NULL)
	{
		printf("Open DesFile ERR:%s\n", desfilename);
		fclose(fin);
		return false;
	}

	fseek(fin, 0, SEEK_END);
	size_t saveinsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	size_t saveoutsize = saveinsize * 1.1 + 1026 * 16;

	unsigned char* inbuff = (unsigned char*)malloc(saveinsize);
	memset(inbuff, 0, saveinsize);
	unsigned char* outbuff = (unsigned char*)malloc(saveoutsize);
	memset(outbuff, 0, saveoutsize);

	unsigned char props[5] = { 0 };
	size_t propsSize = 5;
	size_t readlength = fread(inbuff, 1, saveinsize, fin);

	if (readlength != saveinsize)
	{
		printf("read err\n");
		fclose(fin);
		fclose(fout);
		return false;
	}
	int	res = LzmaCompress(outbuff, &saveoutsize, inbuff, saveinsize,
		props, &propsSize,
		5,
		1 << 24,
		3,
		0,
		2,
		32,
		1);

	if (res != 0)
	{
		printf("LzmaCompressErr:%d\n", res);
		fclose(fin);
		fclose(fout);
		return true;
	}

	int zero = 0;
	fwrite(props, 1, propsSize, fout);
	fwrite(&saveinsize, 1, 4, fout);
	fwrite(&zero, 1, 4, fout);
	fwrite(outbuff, 1, saveoutsize, fout);

	fclose(fin);
	fclose(fout);
	return true;
}

bool MLzma::LzmaFileUncompress(const char* scrfilename, const char* desfilename)
{
	FILE*fin = fopen(scrfilename, "rb");
	if (fin == NULL)
	{
		printf("Open ScrFile ERR:%s\n", scrfilename);
		return false;
	}

	FILE*fout = fopen(desfilename, "wb");
	if (fout == NULL)
	{
		printf("Open DesFile ERR:%s\n", desfilename);
		fclose(fin);
		return false;
	}

	fseek(fin, 0, SEEK_END);
	size_t saveinsize = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	size_t saveoutsize = saveinsize * 1.1 + 1026 * 16;
	unsigned char* inbuff = (unsigned char*)malloc(saveinsize);
	memset(inbuff, 0, saveinsize);

	unsigned char props[5] = { 0 };
	size_t propsSize = 5;

	fread(props, 1, 5, fin);
	fread(&saveoutsize, 1, 4, fin);
	fseek(fin, 4, SEEK_CUR);
	unsigned char* outbuff = (unsigned char*)malloc(saveoutsize);
	size_t readlength = fread(inbuff, 1, saveinsize - 13, fin);

	if (readlength != (saveinsize - 13))
	{
		printf("read err\n");
		fclose(fin);
		fclose(fout);
		return false;
	}

	int	res = LzmaUncompress(outbuff, &saveoutsize, inbuff, &readlength,
		props, propsSize);
	if (res != 0)
	{
		printf("LzmaUncompress:%d\n", res);
		fclose(fin);
		fclose(fout);
		return true;
	}

	fwrite(outbuff, 1, saveoutsize, fout);
	fclose(fin);
	fclose(fout);
	return true;
}

bool MLzma::LzmaStrCompress(const char* scrStr, uint32 srcLen, char** desStr, uint32* destLen)
{
	if (scrStr == nullptr || desStr == nullptr)
	{
		return false;
	}

	// 不能使用 strlen ，因为字符串中可能有 '\0'
	size_t saveinsize = srcLen;
	size_t saveoutsize = saveinsize * 1.1 + 1026 * 16 + LZMA_HEADER_LEN;

	unsigned char* inbuff = (unsigned char*)scrStr;
	unsigned char* outbuff = (unsigned char*)malloc(saveoutsize);		// saveoutsize 这个是申请的空间大小
	memset(outbuff, 0, saveoutsize);

	*desStr = (char*)outbuff;
	unsigned char* startbuff = outbuff;
	outbuff += LZMA_HEADER_LEN;			// 头部信息空间
	unsigned char props[5] = { 0 };
	size_t propsSize = 5;

	// LzmaCompress 执行完成后， saveoutsize 变成真正的大小
	int	res = LzmaCompress(outbuff, &saveoutsize, inbuff, saveinsize,
		props, &propsSize,
		5,
		1 << 24,
		3,
		0,
		2,
		32,
		1);

	if (res != 0)
	{
		printf("LzmaCompressErr:%d\n", res);
		return true;
	}

	int zero = 0;
	// props 中内容可能有 '0'，因此使用 strncpy ，只能使用 memcpy
	memcpy((char*)startbuff, (char*)props, propsSize);
	startbuff += propsSize;
	memcpy((char*)startbuff, (char*)&saveinsize, 4);
	//startbuff += 4;
	//memcpy((char*)startbuff, (char*)zero, 4);

	// 注意 outbuff 这个字符串中间有 '\0' 内容

	if (destLen)
	{
		*destLen = saveoutsize + LZMA_HEADER_LEN;
	}

	return true;
}

bool MLzma::LzmaStrUncompress(const char* scrStr, uint32 srcLen, char** desStr, uint32* destLen)
{
	if (scrStr == nullptr || desStr == nullptr)
	{
		return false;
	}

	size_t saveinsize = srcLen;
	size_t saveoutsize = saveinsize * 1.1 + 1026 * 16;

	unsigned char* inbuff;
	unsigned char* outbuff = (unsigned char*)malloc(saveoutsize);
	*desStr = (char*)outbuff;

	unsigned char props[5] = { 0 };
	size_t propsSize = 5;

	memcpy((char*)props, (char*)scrStr, propsSize);
	scrStr += propsSize;
	memcpy((char*)&saveoutsize, (char*)scrStr, 4);		// 压缩的字符串的长度，这个就是压缩的时候，原始字符串的长度，就是解压缩后的长度
	scrStr += 4;		// 压缩的字符串长度
	scrStr += 4;		// zero
	inbuff = (unsigned char*)scrStr;

	size_t readlength = saveinsize - 13;

	int	res = LzmaUncompress(outbuff, &saveoutsize, inbuff, &readlength,
		props, propsSize);
	if (res != 0)
	{
		return true;
	}

	if (destLen)
	{
		*destLen = saveoutsize;
	}

	return true;
}

END_NAMESPACE_FILEARCHIVETOOL