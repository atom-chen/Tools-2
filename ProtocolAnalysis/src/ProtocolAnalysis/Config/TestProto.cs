using SDK.Lib;
using Game.UI;


namespace Game.Msg
{
	// 自己测试注释-1
	
	public enum CVMsg
	{
		MAX_PASSWORD = 32,
	}

	public class stBase
	{
		public uint32 param;	// 基类成员属性测试

		public stBase()
		{
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(param);
		}
	}

	//自己测试注释-2
	
	public class stTest : stBase
	{
		public uint32 time_1;	// 成员属性测试-1
		public uint32 time_2;	// 成员属性测试-2
		public string strPassword;	// 测试数组成员

		public stTest()
		{
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(time_1);
			bu.writeUnsignedInt32(time_2);
			bu.writeMultiByte(strPassword, GkEncode.UTF8, CVMsg.MAX_PASSWORD);
		}
	}

	// 测试枚举
	public enum eTest
	{
		eValue_1 = 0,	// 测试枚举值
	}

	/**
	 * @brief 多行测试
	 */
	public class stTestMulti : stBase
	{
		public uint32 time;	// 成员属性测试

		public stTestMulti()
		{
			aaa = eTest.eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(time);
		}
	}

}