using System.Text;
using System.IO;
using System;

namespace FileArchiveToolTest
{
	class FileHeader
	{
		protected byte m_pathLen;					// Ŀ¼���ȣ������� '\0'
		protected string m_pFullPath;
		protected string m_fileNamePath;		// �ļ�·������
		protected uint m_fileOffset;				// �ļ������� Archive �е�ƫ��
		protected uint m_fileSize;					// �ļ���С

		public FileHeader()
		{
			
		}

		public void readHeaderFromArchiveFile(MByteBuffer ba)
		{
			m_pathLen = ba.readUnsignedByte();
			m_fileNamePath = ba.readMultiByte(m_pathLen, Encoding.UTF8);
			m_fileOffset = ba.readUnsignedInt();
			m_fileSize = ba.readUnsignedInt();
		}

		public void writeArchiveFile2File(FileStream fileHandle, UnArchiveParam pUnArchiveParam)
		{
			m_pFullPath = pUnArchiveParam.getUnArchiveOutDir() + "/" + m_fileNamePath;

			string strPath = Util.getFullPathNoFileName(m_pFullPath);
			Util.mkDir(strPath);		// ����Ŀ¼

			fileHandle.Seek(m_fileOffset, SeekOrigin.Begin);	// �ƶ����ļ���ʼλ��

			FileStream localFile;
			try
			{
				localFile = new FileStream(m_pFullPath, FileMode.Create);
			}
			catch(Exception error)
			{
				return;
			}

			byte[] pchar;

			if (localFile != null)
			{
				// һ���Զ�ȡ������������Ҫѹ��
				pchar = new byte[m_fileSize];

				uint readlength = (uint)fileHandle.Read(pchar, 0, (int)m_fileSize);
				if (readlength == m_fileSize)
				{
					if (!FileArchiveToolSys.g_pFileArchiveToolSys.getConfigPtr().bCompress())		// �����ѹ��
					{
						localFile.Write(pchar, 0, (int)m_fileSize);
					}
					else	// ��Ҫ��ѹ
					{
						byte[] retChar = null;
						MLzma.DecompressStrLZMA(pchar, m_fileSize, ref retChar, ref m_fileSize);
						localFile.Write(retChar, 0, (int)m_fileSize);
					}
				}
				else							// ��ȡ���������⣬��ȡ���������ļ�
				{

				}

				localFile.Close();
			}
		}
	}
}