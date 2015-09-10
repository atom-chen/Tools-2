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

	class stBase
	{
		public DWORD param;	// 基类成员属性测试

		public stBase()
		{
			param = 1;
		}
	};

	//自己测试注释-2
	
	class stTest : public stBase
	{
		public DWORD time_1;	// 成员属性测试-1
		public DWORD time_2;	// 成员属性测试-2
		public string strPassword;	// 测试数组成员
		public int intArr[CVMsg.MAX_PASSWORD];	// 测试整型数组

		public stTest()
		{
			time_1 = 1;
			time_2 = 1;
			strPassword = "";
			intArr = new int[CVMsg.MAX_PASSWORD];
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
	class stTestMulti : public stBase
	{
		public DWORD time;	// 成员属性测试

		public stTestMulti()
		{
			aaa = eTest.eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
			time = 1;
		}
	};

}

#pragma pack()

#endif