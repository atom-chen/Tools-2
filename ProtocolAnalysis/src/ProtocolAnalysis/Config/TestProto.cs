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
		public uint param;	// 基类成员属性测试

		public stBase()
		{
			param = 1;
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(param);
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readUnsignedInt32(ref param);
		}
	}

	//自己测试注释-2
	
	public class stTest : stBase
	{
		public uint time_1;	// 成员属性测试-1
		public uint time_2;	// 成员属性测试-2
		public string strPassword;	// 测试数组成员
		public int intArr[CVMsg.MAX_PASSWORD];	// 测试整型数组

		public stTest()
		{
			time_1 = 1;
			time_2 = 1;
			strPassword = ;
			intArr = new int[CVMsg.MAX_PASSWORD];
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(time_1);
			bu.writeUnsignedInt32(time_2);
			bu.writeMultiByte(strPassword, GkEncode.UTF8, CVMsg.MAX_PASSWORD);
			
			for(int idx = 0; idx < CVMsg.MAX_PASSWORD; ++idx)
			{
				bu.writeInt32(intArr[idx]);
			}
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readUnsignedInt32(ref time_1);
			bu.readUnsignedInt32(ref time_2);
			bu.readMultiByte(ref strPassword, GkEncode.UTF8, CVMsg.MAX_PASSWORD);
			
			for(int idx = 0; idx < CVMsg.MAX_PASSWORD; ++idx)
			{
				bu.readInt32(ref intArr[idx]);
			}
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
		public uint time;	// 成员属性测试

		public stTestMulti()
		{
			aaa = eTest.eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
			time = 1;
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(time);
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readUnsignedInt32(ref time);
		}
	}

}