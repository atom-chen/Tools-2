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
		public int[] intArr;	// 测试整型数组

		public stTest()
		{
			time_1 = 1;
			time_2 = 1;
			strPassword = "";
			strPassword = "";
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt32(time_1);
			bu.writeUnsignedInt32(time_2);
			bu.writeMultiByte(strPassword, GkEncode.UTF8, CVMsg.MAX_PASSWORD);
			
			for(int idx = 0; idx < (int)CVMsg.MAX_PASSWORD; ++idx)
			{
				intArr[idx].serialize(bu);
			}
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readUnsignedInt32(ref time_1);
			bu.readUnsignedInt32(ref time_2);
			bu.readMultiByte(ref strPassword, GkEncode.UTF8, CVMsg.MAX_PASSWORD);
			intArr = new int[(int)CVMsg.MAX_PASSWORD];
			for(int idx = 0; idx < (int)CVMsg.MAX_PASSWORD; ++idx)
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
			aaa = (int)eTest.eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
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

	/**
	 * @brief 测试结构体数组
	 */
	public class stObject
	{
		public int aaa;

		public stObject()
		{
			aaa = 0;
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeInt32(aaa);
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readInt32(ref aaa);
		}
	}

	public class stUserObject
	{
		public stObject elem;
		public uint size;
		public stObject[] list;

		public stUserObject()
		{
			size = 0;
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			elem = new stObject();
			elem.serialize(bu);
			bu.writeUnsignedInt32(size);
			
			for(int idx = 0; idx < 0; ++idx)
			{
				list[idx].serialize(bu);
			}
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			elem = new stObject();
			elem.derialize(bu);
			bu.readUnsignedInt32(ref size);
			list = new stObject[size];
			for(int idx = 0; idx < 0; ++idx)
			{
				list[idx] = new stObject();
				list[idx].derialize(bu);
			}
		}
	}

}