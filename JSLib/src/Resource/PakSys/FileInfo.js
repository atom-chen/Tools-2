using System.Text;
using System.IO;

namespace SDK.Lib
{
	public class FileHeader
	{
		protected byte m_pathLen;					// Ŀ¼���ȣ������� '\0'
		protected string m_pFullPath;               // ����ֶ���ʱû��ʹ��
		protected string m_fileNamePath;			// �ļ�·������
		protected uint m_fileOffset;				// �ļ������� Archive �е�ƫ��
		protected uint m_fileSize;					// �ļ���С
		protected uint m_flags;						// ��ʶ�ֶ�

		public FileHeader()
		{
			
		}

        public string pFullPath
        {
            get
            {
                return m_pFullPath;
            }
            set
            {
                m_pFullPath = value;
            }
        }

        public string fileNamePath
        {
            get
            {
                return m_fileNamePath;
            }
        }

        public uint fileSize
        {
            get
            {
                return m_fileSize;
            }
            set
            {
                m_fileSize = value;
            }
        }

		public void readHeaderFromArchiveFile(ByteBuffer bu)
		{
            bu.readUnsignedInt8(ref m_pathLen);
            bu.readMultiByte(ref m_fileNamePath, m_pathLen, Encoding.UTF8);
            bu.readUnsignedInt32(ref m_fileOffset);
            bu.readUnsignedInt32(ref m_fileSize);
            bu.readUnsignedInt32(ref m_flags);
		}

        public void readArchiveFile2Bytes(FileStream fileHandle, ref byte[] bytes)
		{
			fileHandle.Seek(m_fileOffset, SeekOrigin.Begin);	// �ƶ����ļ���ʼλ��

            uint readlength = (uint)fileHandle.Read(bytes, 0, (int)m_fileSize);
			if (readlength == m_fileSize)
			{
                if (!UtilPak.checkFlags(FileHeaderFlag.eFHF_CPS, ref m_flags))
				{
					
				}
				else	// ��Ҫ��ѹ
				{
					byte[] retChar = null;
                    MLzma.DecompressStrLZMA(bytes, m_fileSize, ref retChar, ref m_fileSize);
                    bytes = retChar;
				}
			}
		}

        // ��ǰ�ļ��Ƿ�ѹ��
        public bool bCompress()
        {
            return UtilPak.checkFlags(FileHeaderFlag.eFHF_CPS, ref m_flags);
        }
	}
}