namespace FileArchiveToolTest
{
	public class UnArchiveParam
	{
		protected string m_punArchiveFilePath;
		protected string m_punArchiveOutDir;

		public UnArchiveParam()
		{
			
		}

		public void setUnArchiveFilePath(string pPath)
		{
			m_punArchiveFilePath = pPath;
		}

		public void setUnArchiveOutDir(string pPath)
		{
			m_punArchiveOutDir = pPath;
		}

		public string getUnArchiveFilePath()
		{
			return m_punArchiveFilePath;
		}

		public string getUnArchiveOutDir()
		{
			return m_punArchiveOutDir;
		}
	}
}