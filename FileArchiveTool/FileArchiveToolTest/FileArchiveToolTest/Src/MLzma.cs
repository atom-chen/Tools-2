using System;
using System.IO;

namespace FileArchiveToolTest
{
	/**
	 * @brief Lzma 算法
	 */
	public class MLzma
	{
		public const uint LZMA_HEADER_LEN = 13;
		public MLzma ()
		{

		}

		public static void CompressFileLZMA (string inFile, string outFile)
		{
			SevenZip.Compression.LZMA.Encoder coder = new SevenZip.Compression.LZMA.Encoder ();
			FileStream input = new FileStream (inFile, FileMode.Open);
			FileStream output = new FileStream (outFile, FileMode.Create);

			// Write the encoder properties
			coder.WriteCoderProperties (output);
			// Write the decompressed file size.
			output.Write (BitConverter.GetBytes (input.Length), 0, 8);

			// Encode the file.
			coder.Code (input, output, input.Length, -1, null);
			output.Flush ();
			output.Close ();
			input.Close ();
		}

		public static void DecompressFileLZMA (string inFile, string outFile)
		{
			SevenZip.Compression.LZMA.Decoder coder = new SevenZip.Compression.LZMA.Decoder ();
			FileStream input = new FileStream (inFile, FileMode.Open);
			FileStream output = new FileStream (outFile, FileMode.Create);

			// Read the decoder properties
			byte[ ] properties = new byte [ 5 ];
			input.Read (properties, 0, 5);

			// Read in the decompress file size.
			byte[ ] fileLengthBytes = new byte [ 8 ];
			input.Read (fileLengthBytes, 0, 8);
			long fileLength = BitConverter.ToInt64 (fileLengthBytes, 0);

			// Decompress the file.
			coder.SetDecoderProperties (properties);
			coder.Code (input, output, input.Length, fileLength, null);
			output.Flush ();
			output.Close ();
			input.Close ();
		}

		public static uint CompressStrLZMA (byte[] inBytes, byte[] outBytes)
		{
			SevenZip.Compression.LZMA.Encoder coder = new SevenZip.Compression.LZMA.Encoder ();
			MemoryStream inputStream = new MemoryStream (inBytes);
			int saveinsize = inBytes.Length;
			int saveoutsize = (int)(saveinsize * 1.1 + 1026 * 16 + LZMA_HEADER_LEN);

			outBytes = new byte[saveoutsize];
			MemoryStream outStream = new MemoryStream (outBytes);

			// Write the encoder properties
			coder.WriteCoderProperties (outStream);
			// Write the decompressed file size.
			outStream.Write (BitConverter.GetBytes (inputStream.Length), 0, 8);

			// Encode the file.
			coder.Code (inputStream, outStream, saveinsize, saveoutsize, null);
			outStream.Flush ();
			outStream.Close ();
			inputStream.Close ();

			return (uint)saveoutsize;
		}

		public static uint DecompressStrLZMA (byte[] inBytes, byte[] outBytes)
		{
			SevenZip.Compression.LZMA.Decoder coder = new SevenZip.Compression.LZMA.Decoder ();
			MemoryStream inStream = new MemoryStream(inBytes);

			uint saveinsize = (uint)inBytes.Length;
			uint saveoutsize = (uint)(saveinsize * 1.1 + 1026 * 16);
			outBytes = new byte[saveoutsize];
			MemoryStream outStream = new MemoryStream (outBytes);

			// Read the decoder properties
			byte[ ] properties = new byte [ 5 ];
			inStream.Read (properties, 0, 5);

			// Read in the decompress file size.
			byte[ ] fileLengthBytes = new byte [ 8 ];
			inStream.Read (fileLengthBytes, 0, 8);
			long fileLength = BitConverter.ToInt64 (fileLengthBytes, 0);

			// Decompress the file.
			coder.SetDecoderProperties (properties);
			coder.Code (inStream, outStream, fileLength, saveoutsize, null);
			outStream.Flush ();
			outStream.Close ();
			inStream.Close ();

			return saveoutsize;
		}
	}
}