

namespace Cmd
{
	//////////////////////////////////////////////////////////////
	// 空指令定义开始
	//////////////////////////////////////////////////////////////
	public enum eNullUserCmd
	{
		NULL_USERCMD_PARA = 0,
	}

	public class stNullUserCmd
	{
		public byte byCmd;
		public byte byParam;
		public uint dwTimestamp;

		public stNullUserCmd()
		{
			byCmd = 0;
			byParam = 0;
			dwTimestamp = 0;
		}

		override public void serialize(ByteBuffer bu)
		{
			base.serialize(bu)
			bu.writeUnsignedInt8(byCmd);
			bu.writeUnsignedInt8(byParam);
			bu.writeUnsignedInt32(dwTimestamp);
		}

		override public void derialize(ByteBuffer bu)
		{
			base.derialize(bu)
			bu.readUnsignedInt8(ref byCmd);
			bu.readUnsignedInt8(ref byParam);
			bu.readUnsignedInt32(ref dwTimestamp);
		}
	}

	//////////////////////////////////////////////////////////////
	// 空指令定义结束
	//////////////////////////////////////////////////////////////
}