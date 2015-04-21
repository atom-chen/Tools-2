#ifndef __FileHeaderFlag_H
#define __FileHeaderFlag_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
*@brief �ļ�ͷ��ʶ���Ƕ�Ӧ��ֵ
*/
enum FILEARCHIVETOOL_EXPORT FileHeaderFlagIndex
{
	eFHFI_CPS,		// ѹ��λ
};

/**
*@brief �ļ�ͷ��ʶ��������
*/
enum FILEARCHIVETOOL_EXPORT FileHeaderFlag
{
	eFHF_CPS = 1 << 0,		// ѹ��λ
};

END_NAMESPACE_FILEARCHIVETOOL

#endif