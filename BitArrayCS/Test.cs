using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BitArrayCS
{
    class Test
    {
        static void Main(string[] args)
        {
            const int length = 128;
            /*
            Example : storing and retrievening this data to and from a 12 bytes (96 bits) BitArray
            data	number of bits to store
            bool	1
            bool	1
            bool	1
            int	6
            float	32
            char	8
            long	32
            int	4
            bool	1
            bool	2
            bool	3
            int	4
            bool	1
            byteArray[4]	31
            int	4
            */
            Console.WriteLine("TEST BITARRAY.\n");

            byte[] byteArray = new byte[4]{ 0x45, 0x72, 0x78, 0x7 };
            bool b1 = false, b2 = false, b3 = false, b4 = false, b5 = false, b6 = false, b7 =false;
            int i1 = 0, i2 = 0, i3 = 0, i4=0;
            byte c1=0;
            float f1=0;
            long l1=0;
            // Store 
            BitArray bitArray = new BitArray(length);
            bitArray.SetBit(0, true);
            bitArray.SetBit(1, false);
            bitArray.SetBit(2, true);
            bitArray.StoreInt(6, 3, 37);
            bitArray.StoreFloat(9, (float)46.582842);
            bitArray.StoreChar(8, 41, 255);
            bitArray.StoreLong(32, 49, 46582842);
            bitArray.StoreInt(4, 81, 14);
            bitArray.SetBit(85, true);
            bitArray.SetBit(86, true);
            bitArray.SetBit(87, true);
            bitArray.StoreInt(4, 88, 13);
            bitArray.SetBit(92, true);
            bitArray.StoreBits(31, 0, 93, byteArray);
            bitArray.StoreInt(4, 124, 12);
            // Retrieve
            bitArray.Bit(0, ref b1);
            bitArray.Bit(1, ref b2);
            bitArray.Bit(2, ref b3);
            bitArray.RetrieveInt(6, 3, ref i1);
            bitArray.RetrieveFloat(9, ref f1);
            bitArray.RetrieveChar(8, 41, ref c1);
            bitArray.RetrieveLong(32, 49, ref l1);
            bitArray.RetrieveInt(4, 81, ref i2);
            bitArray.Bit(85, ref b4);
            bitArray.Bit(86, ref b5);
            bitArray.Bit(87, ref b6);
            bitArray.RetrieveInt(4, 88, ref i3);
            bitArray.Bit(92, ref b7);
            bitArray.RetrieveByteArray(31, 93, byteArray);
            bitArray.RetrieveInt(4, 124, ref i4);
            // Print everything
            Console.WriteLine("b1: {0}", b1);
            Console.WriteLine("b2: {0}", b2);
            Console.WriteLine("b3: {0}", b3);
            Console.WriteLine("i1: {0}", i1);
            Console.WriteLine("f1: {0}", f1);
            Console.WriteLine("c1: {0}", c1);
            Console.WriteLine("l1: {0}", l1);
            Console.WriteLine("i2: {0}", i2);
            Console.WriteLine("b4: {0}", b4);
            Console.WriteLine("b5: {0}", b5);
            Console.WriteLine("b6: {0}", b6);
            Console.WriteLine("i3: {0}", i3);

            // Print bitArray
            byte[] buffer;
            buffer = bitArray.ByteArray;
            int i;
            for (i = 0; i < buffer.Length; i++)
            {
                if (i > 0) Console.Write(":");
                Console.Write("{0}: ", buffer[i]);
            }
            Console.WriteLine();
            Console.ReadKey();
            return;
        }
    }
}
