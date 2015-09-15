#ifndef _stTestProto_h
#define _stTestProto_h

#include "aaa/bbb.h"
#include "dddd/gggg.h"

#pragma pack(1)

namespace Game.Msg
{
	// 自己测试注释-1
	enum CVMsg
	{
		MAX_PASSWORD = 32,
	};

	struct stBase
	{
		DWORD param;	// 基类成员属性测试

		public stBase()
		{
			param = 1;
		}
	};

	//自己测试注释-2
	struct stTest : public stBase
	{
		DWORD time_1;	// 成员属性测试-1
		DWORD time_2;	// 成员属性测试-2
		string strPassword;	// 测试数组成员
		int intArr[MAX_PASSWORD];	// 测试整型数组

		public stTest()
		{
			time_1 = 1;
			time_2 = 1;
			strPassword = {0};
			intArr = {0};
		}
	};

	// 测试枚举
	enum eTest
	{
		eValue_1 = 0,	// 测试枚举值
	};

	/**
	 * @brief 多行测试
	 */
	struct stTestMulti : public stBase
	{
		DWORD time;	// 成员属性测试

		public stTestMulti()
		{
			aaa = eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
			time = 1;
		}
	};

	/**
	 * @brief 测试结构体数组
	 */
	struct stObject
	{
		int aaa;

		public stObject()
		{
			aaa = 0;
		}
	};

	struct stUserObject
	{
		stObject elem;
		DWORD size;
		stObject list[0];

		public stUserObject()
		{
			size = 0;
		}
	};

}

#pragma pack()

#endif