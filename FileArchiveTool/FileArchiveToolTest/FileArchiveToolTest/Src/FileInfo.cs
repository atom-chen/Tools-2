using System.Text;
using System.IO;
using System;

namespace FileArchiveToolTest
{
	class FileHeader
	{
		protected byte m_pathLen;					// 目录长度，不包括 '\0'
		protected string m_pFullPath;
		protected string m_fileNamePath;		// 文件路径名字
		protected uint m_fileOffset;				// 文件在整个 Archive 中的偏移
		protected uint m_fileSize;					// 文件大小

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
			Util.mkDir(strPath);		// 创建目录

			fileHandle.Seek(m_fileOffset, SeekOrigin.Begin);	// 移动到文件开始位置

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
				// 一次性读取进来，可能需要压缩
				pchar = new byte[m_fileSize];

				uint readlength = (uint)fileHandle.Read(pchar, 0, (int)m_fileSize);
				if (readlength == m_fileSize)
				{
					if (!FileArchiveToolSys.g_pFileArchiveToolSys.getConfigPtr().bCompress())		// 如果不压缩
					{
						localFile.Write(pchar, 0, (int)m_fileSize);
					}
					else	// 需要解压
					{
						byte[] retChar = null;
						MLzma.DecompressStrLZMA(pchar, m_fileSize, ref retChar, ref m_fileSize);
						localFile.Write(retChar, 0, (int)m_fileSize);
					}
				}
				else							// 读取可能有问题，读取不了完整文件
				{

				}

				localFile.Close();
			}
		}
	}
}