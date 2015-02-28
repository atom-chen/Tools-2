using System.IO;
using System.Text;

namespace FileArchiveToolTest
{
	class ArchiveHeader
	{
		public const uint ARCHIVETOOL_VERSION = 101100;

		public byte[] m_magic;			// ����
		public byte m_endian;				// ��С��
		public uint m_headerSize;		// ͷ����С
		public uint m_version;			// �汾
		public uint m_fileCount;			// �ļ��ܹ�����

		public ArchiveHeader()
		{
			m_version = ARCHIVETOOL_VERSION;

			m_magic = new byte[4];
			m_magic[0] = (byte)'a';
			m_magic[1] = (byte)'s';
			m_magic[2] = (byte)'d';
			m_magic[3] = (byte)'f';

			m_endian = (byte)Endian.LITTLE_ENDIAN;		// 0 ��� 1 С��
		}

		public void clear()
		{
			m_fileCount = 0;
			m_headerSize = 0;
		}

		public bool readArchiveFileHeader(FileStream fileHandle, MByteBuffer pMByteBuffer)
		{
			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, 4);
			pMByteBuffer.length = 4;
			string magic = pMByteBuffer.readMultiByte(4, Encoding.UTF8);
			if (magic != "asdf")		// ��� magic
			{
				return false;
			}

			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, (int)calcArchiveHeaderSizeNoFileHeader() - 4);
			pMByteBuffer.length = calcArchiveHeaderSizeNoFileHeader() - 4;
			// ��ȡ endian 
			m_endian = pMByteBuffer.readByte ();
			pMByteBuffer.setEndian((Endian)m_endian);

			// ��ȡͷ����С
			m_headerSize = pMByteBuffer.readUnsignedInt();

			// ��ȡ�汾
			m_version = pMByteBuffer.readUnsignedInt();
			// ��ȡ�ļ�����
			m_fileCount = pMByteBuffer.readUnsignedInt();

			// ��ȡ����ͷ
			pMByteBuffer.clear ();
			fileHandle.Read(pMByteBuffer.dynBuff.buff, 0, (int)(m_headerSize - calcArchiveHeaderSizeNoFileHeader()));
			pMByteBuffer.length = m_headerSize - calcArchiveHeaderSizeNoFileHeader ();

			return true;
		}

		public uint calcArchiveHeaderSizeNoFileHeader()
		{
			// д�� magic 
			// д�� endian 
			// д��ͷ���ܹ���С
			// д��汾
			// д���ļ�����
			return (uint)m_magic.Length + sizeof(byte) + sizeof(uint) + sizeof(uint) + sizeof(uint);
		}
	}
}