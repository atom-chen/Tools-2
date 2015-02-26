#include "DynBufResizePolicy.h"
#include "BufferDefaultValue.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

// ��ȡһ������Ĵ�С
uint32 DynBufResizePolicy::getCloseSize(uint32 needSize, uint32 capacity)
{
	uint32 ret = 0;

	if (needSize <= MAX_CAPACITY)
	{
		if (capacity >= needSize)
		{
			ret = capacity;
		}
		else
		{
			ret = 2 * capacity;
			while (ret < needSize && ret < MAX_CAPACITY)
			{
				ret *= 2;
			}

			if (ret > MAX_CAPACITY)
			{
				ret = MAX_CAPACITY;
			}
		}
	}
	else	// ��Ҫ�����ݱ���������������Ĵ�С����
	{
		// ��־����Ҫ�Ĵ洢�ռ�̫��
	}

	return ret;
}

END_NAMESPACE_FILEARCHIVETOOL