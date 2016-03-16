using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Data;
using Ris;

namespace PulseDevelop
{
    public class PulseFile
    {
        struct WavFileHeader
        {
            public byte[] riffID;
            public uint size;
            public byte[] wavID;
            public byte[] fmtID;
            public uint fmtSize;
            public ushort format;
            public ushort channels;
            public uint sampleRate;
            public uint bytePerSec;
            public ushort blockSize;
            public ushort bit;
            public byte[] dataID;
            public uint dataSize;
        }

        public static void WriteToWaveFile(PulseSignal ss)
        {
            // Local
            WavFileHeader header = new WavFileHeader();

            // Local
            string filePath = @"C:\Prime\Pulse\" + ss.Name + @".wav";
            uint dataSize = (uint)ss.NumSamples * 2;
            uint sampleRate = (uint)ss.Fs;
            uint bytePerSec = 2 * sampleRate;

            // Set file header
            header.riffID = new byte[4] { 0x52, 0x49, 0x46, 0x46 };
            header.size = 36 + dataSize;
            header.wavID = new byte[4] { 0x57, 0x41, 0x56, 0x45 };
            header.fmtID = new byte[4] { 0x66, 0x6d, 0x74, 0x20 };
            header.fmtSize = 16;
            header.format = 1;
            header.channels = 1;
            header.sampleRate = sampleRate;
            header.bytePerSec = bytePerSec;
            header.blockSize = 2;
            header.bit = 16;
            header.dataID = new byte[4] { 0x64, 0x61, 0x74, 0x61 };
            header.dataSize = dataSize;

            using (FileStream fs = new FileStream(filePath, FileMode.Create, FileAccess.Write))
            using (BinaryWriter bw = new BinaryWriter(fs))
            {
                try
                {
                    // Write file header
                    bw.Write(header.riffID);
                    bw.Write(header.size);
                    bw.Write(header.wavID);
                    bw.Write(header.fmtID);
                    bw.Write(header.fmtSize);
                    bw.Write(header.format);
                    bw.Write(header.channels);
                    bw.Write(header.sampleRate);
                    bw.Write(header.bytePerSec);
                    bw.Write(header.blockSize);
                    bw.Write(header.bit);
                    bw.Write(header.dataID);
                    bw.Write(header.dataSize);

                    // Write file data
                    for (int i = 0; i < ss.NumSamples; i++)
                    {
                        // Convert double -1.0..1.0 to short -32768..32768
                        int x32 = (int)(32768.0 * ss.X[i]);
                        if (x32 > 32767) x32 = 32767;
                        if (x32 < -32768) x32 = -32768;
                        short x16 = (short)x32;
                        // Write short
                        bw.Write(x16);
                    }
                }
                finally
                {
                    if (bw != null)
                    {
                        bw.Close();
                    }
                    if (fs != null)
                    {
                        fs.Close();
                    }
                }
            }
        }

        public static void WriteToTextFile(PulseSignal ss,int nsamples)
        {
            // Local
            string filePath = @"C:\MyLib\Data\" + ss.Name + @".csv";

            using (StreamWriter sw = File.CreateText(filePath))
            {
                try
                {
                    // Write file data
                    for (int k = 0; k < nsamples; k++)
                    {
                        // Write time and data
                        double t = k * ss.Ts;
                        sw.WriteLine("{0},{1}",t,ss.X[k]);
                    }
                }
                finally
                {
                    if (sw != null)
                    {
                        sw.Close();
                    }
                }
            }
        }
    }
}
