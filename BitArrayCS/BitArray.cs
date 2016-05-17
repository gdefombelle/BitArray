/*
 
    Copyright(C) <2016>  <Gabriel J. de Fombelle>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see<http://www.gnu.org/licenses/>.

    my email: gabriel.de.fombelle@gmail.com

*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BitArrayCS
{
    public class BitArray
    {
        bool BIG_ENDIAN = false; // default is LITTLE_ENDIAN
        byte[] byteArray;
        int byteArrayCount;
        byte[] _baChar = new byte[sizeof(char)];
        byte[] _baInt = new byte[sizeof(int)];
        byte[] _baLong = new byte[sizeof(long)];
        // 2 power 32 was deliberately changed to 2 32 -1 () power to be contained in 32-bit
        UInt32[] _power2 = new UInt32[33]{1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,
    		2097152,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 ,2147483648 ,4294967295 };

    public BitArray(int bitSize)
        {
            byteArrayCount = ((bitSize + 7) / 8);
            byteArray = new byte[ByteArrayCount];
            Initialize();
        }

        public byte[] ByteArray
        {
            get
            {
                return byteArray;
            }
        }

        public int ByteArrayCount
        {
            get
            {
                return byteArrayCount;
            }
        }

        void Initialize()
        {
            for (int i = 0; i < ByteArrayCount; i++)
            {
                ByteArray[i] = 0;
            }
            BIG_ENDIAN = !IsBigEndian();
        }
        bool IsBigEndian()
        {
            return BitConverter.IsLittleEndian;
        }

        // ******************* Store ************************************

        public int SetBit(int atBitPos, bool b)
        {
            if (atBitPos > byteArrayCount * sizeof(char) * 8) return 0;
            if (b) byteArray[atBitPos / 8] |=(byte) (1 << (atBitPos % 8));
            else byteArray[atBitPos / 8] &= (byte)~(1 << (atBitPos % 8));
            return 1;
        }
        public int ToggleBit(int atBitPos, ref bool b)
        {
            if (atBitPos > byteArrayCount * sizeof(char)) return 0;
            byteArray[atBitPos / 8] ^= (byte)(1 << (atBitPos % 8));
            b = (byteArray[atBitPos / 8] & (1 << (atBitPos % 8))) !=0;
            return 1;
        }

        public int StoreInt(int nbits, int atBitPos, int value)
        {
            if (nbits > sizeof(int) * 8) return 0;
            // check for possible overflow
            if (value >= _power2[nbits]) return -1;
            // negative value cannotbe truncated
            if (value < 0 && nbits != sizeof(int) * 8) return -2;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(nbits, 0, atBitPos, bytes);
        }
        public int StoreUInt(int nbits, int atBitPos, uint value)
        {
            if (nbits > sizeof(int) * 8) return 0;
            // check for possible overflow
            if (value < 0 && nbits != sizeof(int) * 8) return -2;
            if (value >= _power2[nbits]) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(nbits, 0, atBitPos, bytes);
        }
        public int StoreChar(int nbits, int atBitPos, byte value)
        {
            if (nbits > sizeof(char) * 8) return 0;
            // check for possible overflow
            if (value >= _power2[nbits]) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(nbits, 0, atBitPos, bytes);
        }

        public int StoreLong(int nbits, int atBitPos, long value)
        {
            if (nbits > sizeof(long) * 8) return 0;
            // negative value cannotbe truncated
            if (value < 0 && nbits != sizeof(long) * 8) return -2;
            // check for possible overflow
            if (value >= _power2[nbits - 1]) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(nbits, 0, atBitPos, bytes);
        }
        public int StoreULong(int nbits, int atBitPos, ulong value)
        {
            if (nbits > sizeof(long) * 8) return 0;
            // check for possible overflow
            if (value >= _power2[nbits]) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(nbits, 0, atBitPos, bytes);
        }
        public int StoreFloat(int atBitPos, float value)
        {
            int len = sizeof(float);
            if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(len*8, 0, atBitPos, bytes);
        }
        public int StoreDouble(int atBitPos, double value)
        {
            int len = sizeof(double);
            if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
            byte[] bytes = BitConverter.GetBytes(value);
            return StoreBits(len * 8, 0, atBitPos, bytes);
        }

        //******************* Retrieve *********************
        public int Bit(int atBitPos, ref bool b)
        {
            if (atBitPos > byteArrayCount * sizeof(char) * 8) return -1;
            b = (byteArray[atBitPos / 8] & (1 << (atBitPos % 8))) !=0;
            return 1;
        }
        public int RetrieveByteArray(int nbits, int atBitPos, byte[] buffer)
        {
            if (nbits > buffer.Length * sizeof(char) * 8) return -1;
            for (int i = 0; i < buffer.Length; i++) buffer[i] = 0;

            int cursorBuffer = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
            {
                bool b = (byteArray[i / 8] & (1 << (i % 8)))!=0;
                if (b) buffer[cursorBuffer / 8] |= (byte)(1 << (cursorBuffer % 8));
                else buffer[cursorBuffer / 8] &= (byte)~(1 << (cursorBuffer % 8));
                cursorBuffer++;
            }
            if (BIG_ENDIAN) buffer = ReverseByteArray(buffer);
            return 1;
        }
        public int RetrieveInt(int nbits, int atBitPos, ref int toInt)
        {
            int len = sizeof(int);
            if (nbits > len * 8) return -1;
            toInt = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
                toInt |= (int)GetBit(i) << (i - atBitPos);
            return 1;
        }
        public int RetrieveUInt(int nbits, int atBitPos, ref uint toUint)
        {
            int len = sizeof(int);
            if (nbits > len * 8) return -1;
            toUint = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
                toUint |= (uint)GetBit(i) << (i - atBitPos);
            return 1;
        }
        public int RetrieveULong(int nbits, int atBitPos, ref ulong toUlong)
        {
            int len = sizeof(int);
            if (nbits > len * 8) return -1;
            toUlong = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
                toUlong |= (ulong)GetBit(i) << (i - atBitPos);
            return 1;
        }
        public int RetrieveLong(int nbits, int atBitPos, ref long toLong)
        {
            int len = sizeof(int);
            if (nbits > len * 8) return -1;
            toLong = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
                toLong |= (long)GetBit(i) << (i - atBitPos);
            return 1;
        }
        public int RetrieveFloat(int atBitPos, ref float toFloat)
        {
            int len = sizeof(float);
            if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
            byte[] buffer = new byte[len];
            RetrieveByteArray(len * 8, atBitPos, buffer);
            double _d = BitConverter.ToSingle(buffer, 0);
            toFloat = (float)_d;
            return 1;
        }
        public int RetrieveDouble(int atBitPos, ref double toDouble)
        {
            int len = sizeof(float);
            if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
            byte[] buffer = new byte[len];
            RetrieveByteArray(len * 8, atBitPos, buffer);
            toDouble = BitConverter.ToDouble(buffer, 0);
            return 1;
        }
        public int RetrieveChar(int nbits, int atBitPos, ref byte toChar)
        {
            if (nbits > sizeof(char) * 8) return -1;
            toChar = 0;
            for (int i = atBitPos; i < atBitPos + nbits; i++)
                toChar |= (byte)((int)GetBit(i) << (i - atBitPos));
            return 1;
        }

        // ****************** private  *********************************
        public int StoreBits(int nbits, int fromSourceStartingBit, int atTargetStartingBit, byte[] value)
        {
            int ret = 1;
            if (atTargetStartingBit + nbits > byteArrayCount * 8) return 3;
            //if (fromSourceStartingBit + nbits > sizeof(value) * sizeof(char) * 8) return 5;
            //
            // convert byte array to LITTLE_ENDIAN
            if (BIG_ENDIAN) value = ReverseByteArray(value);

            int sourceEndingByte = Math.Max((fromSourceStartingBit + nbits) / 8 - 1, 0);
            int sourceEndingBit = Math.Max(fromSourceStartingBit + nbits - 1,0);
            int targetEndingBit = Math.Max(nbits + atTargetStartingBit - 1,0);
            int targetStartingByte = atTargetStartingBit / 8;
            int targetEndingByte = (targetEndingBit) / 8;

            int currentTargetByte = targetStartingByte;


            int cursorTargetGlobalBit = atTargetStartingBit;
            int cursorSourceGlobalBit = fromSourceStartingBit;


            while (cursorSourceGlobalBit <= sourceEndingBit)
            {
                int cursorSourceLocalBit = cursorSourceGlobalBit % 8;
                int cursorTargetLocalBit = cursorTargetGlobalBit % 8;
                int cursorTargetByte = cursorTargetGlobalBit / 8;
                int currentSourceByte = cursorSourceGlobalBit / 8;
                int bitPacketSize = Math.Min(sourceEndingBit - cursorSourceGlobalBit + 1, Math.Min(7 - cursorSourceLocalBit + 1, 7 - cursorTargetLocalBit + 1));
                InsertBitsFromByteToByte(value[currentSourceByte], cursorSourceLocalBit, cursorTargetByte, cursorTargetLocalBit, bitPacketSize);
                cursorSourceGlobalBit += bitPacketSize;
                cursorTargetGlobalBit += bitPacketSize;
            }

            return ret;
        }

        byte[] ReverseByteArray(byte[] byteArray)
        {
            return byteArray.Reverse().ToArray();
        }
        void InsertBitsFromByteToByte(byte sourceByte, int sourceBitStartIndex, int targetByteIndex, int targetBitStartIndex, int nbits)
        {
            byte valueToInsert;
            valueToInsert = (byte)(OneByteMask(sourceBitStartIndex, sourceBitStartIndex + nbits - 1) & sourceByte);
            valueToInsert = (byte)(valueToInsert >> sourceBitStartIndex);
            valueToInsert = (byte)(valueToInsert << targetBitStartIndex);
            byte mask2 = (byte)(~OneByteMask(targetBitStartIndex, targetBitStartIndex + nbits - 1));
            byteArray[targetByteIndex] = (byte)(byteArray[targetByteIndex] & mask2);
            byteArray[targetByteIndex] = (byte)(byteArray[targetByteIndex] | valueToInsert);
        }
        byte OneByteMask(int from, int to)
        {
            byte r = 0;
            for (int i = from; i <= to; i++)
                r |= (byte)(1 << (byte)i);
            return r;
        }

        int GetBit(int atPos)
        {
            byte c = (byte)(byteArray[atPos / 8] & (1 << (atPos % 8)));
            return (c == 0 ? 0 : 1);
        }

    }
}
