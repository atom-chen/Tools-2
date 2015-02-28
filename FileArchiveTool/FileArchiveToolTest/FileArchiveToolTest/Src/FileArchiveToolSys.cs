namespace FileArchiveToolTest
{
	public class FileArchiveToolSys
	{
		public static FileArchiveToolSys g_pFileArchiveToolSys = new FileArchiveToolSys();		// 全局接口

		protected Config m_pConfig;

		public FileArchiveToolSys()
		{
			m_pConfig = new Config();
		}

		public Config getConfigPtr()
		{
			return m_pConfig;
		}
	}
}