namespace FileArchiveToolTest
{
	public class ArchiveData
	{
		protected PakItem m_pPakItem;

		public ArchiveData()
		{
			m_pPakItem = new PakItem();
		}

		public void unArchiveFile(UnArchiveParam pUnArchiveParam)
		{
			m_pPakItem.clearFileVec();
			m_pPakItem.writeArchiveFile2File(pUnArchiveParam);
		}
	}
}