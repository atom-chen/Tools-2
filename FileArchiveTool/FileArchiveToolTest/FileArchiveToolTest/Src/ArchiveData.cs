using System.Collections.Generic;
using System.IO;
using System;

namespace FileArchiveToolTest
{
	class ArchiveData
	{
		protected ArchiveHeader m_pArchiveHeader;
		protected uint m_fileSize;			// �ļ��ܹ���С
		protected List<FileHeader> m_pFileVec;		// �����ļ��б�

		public ArchiveData()
		{
			m_pArchiveHeader = new ArchiveHeader();
			m_pFileVec = new List<FileHeader>();
		}

		public void unArchiveFile(UnArchiveParam pUnArchiveParam)
		{
			clearFileVec();
			writeArchiveFile2File(pUnArchiveParam);
		}

		public void clearFileVec()
		{
			m_fileSize = 0;
			m_pArchiveHeader.clear();
			m_pFileVec.Clear();
		}

		public void readArchiveFileHeader(FileStream fileHandle)
		{
			MByteBuffer pMByteBuffer = new MByteBuffer();

			if (m_pArchiveHeader.readArchiveFileHeader(fileHandle, pMByteBuffer))		// ��� magic
			{
				FileHeader pFileHeader;
				for (uint idx = 0; idx < m_pArchiveHeader.m_fileCount; ++idx)
				{
					pFileHeader = new FileHeader();
					m_pFileVec.Add(pFileHeader);
					pFileHeader.readHeaderFromArchiveFile(pMByteBuffer);
				}
			}
		}

		public void writeArchiveFile2File(UnArchiveParam pUnArchiveParam)
		{
			FileStream fileHandle;

			try
			{
				fileHandle = new FileStream(pUnArchiveParam.getUnArchiveFilePath(), FileMode.Open);
			}
			catch(Exception error)
			{
				return;
			}

			if (fileHandle != null)
			{
				readArchiveFileHeader(fileHandle);

				// д��ͷ��
				foreach (FileHeader item in m_pFileVec)
				{
					item.writeArchiveFile2File(fileHandle, pUnArchiveParam);
				}

				fileHandle.Close ();
			}
		}
	}
}