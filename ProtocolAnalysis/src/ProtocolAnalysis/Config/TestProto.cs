using SDK.Lib;

namespace Game.Msg
{
	// 自己测试注释-1


	public class stBase
	{
		public uint32 param;	// 基类成员属性测试

		public stBase()
		{
			
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
		}
	}

	//自己测试注释-2


	public class stTest : stBase
	{
		public uint32 time;	// 成员属性测试

		public stTest()
		{
			
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
		}
	}

	// 测试枚举

	/**
 * @brief 多行测试
 */

	public class stTestMulti : stBase
	{
		public uint32 time;	// 成员属性测试

		public stTestMulti()
		{
			
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
		}
	}
}