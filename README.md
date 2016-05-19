# BitArray
C++, C#, Javascript, ... set of  libraries to easily store and retrieve bits sequences to and from a, array of bytes 
PROJECT BITARRAY 

Note BitArray.JS is stille under develeopment

GOAL
BitArray is a set of libraries C/C++, C#, ...  class library specially designed for IoT and embedded software developers to easily compact and retrieve data stored as bit sequences of an arbitrary length (i.e. not necessarily multiple of 8 ) into array of bytes, not aligning data against bytes but bits. BitArray avoid annoying and quite often long programming to do that. The library would be particularly useful in IoT programming for carrying data over low throughput networks such as Ultra Narrow Band networks like Sigfox, LoRa, etc.
Basically BitArray provides methods for 
1.	Simply insert n bits from a source (int, long, float, double, char, bool, byte[]) toward  a BitArray starting at a given bit index. You can also append any data to the byte array without worrying about the bit index 
2.	Retrieve data from the BitArray within a bit range into regular basic typed data such as int, long, float, double, char, bool, byte[], etc.
Compatibility: BitArray lib is designed to be compatible with most of compilers including limited C++ such Arduino.
BASICS
The bit array is actually stored into an array of unsigned chars in a right to left order i.e. bit0 is the rightmost  least significant bit of bit set, therefore the internal unsigned char array is Little_endianed.


Error: Most of methods return an int that hold an error code or true if ok. (as some compilers do not handle exception)
STORING BITS SEQUENCE
The basic method that BitArray provides is StoreBits that store n bits from an array of bytes starting a bit position toward the internal bit array at a bit position.  Endian parameter is to tell the lib whether the source byte array to insert is originally Little_endianed or not. 
int StoreBits(int nbits, int fromStartingBit, int atStartingBit, unsigned char from[], int length);
STORING REGULAR TYPED DATA 
On top of StoreBits a set of useful methods offered to directly store some bits of standards type into BitArray like:
•	int SetBit(int atBitPos,bool b);
•	int ToggleBit (int atBitPos, bool *b);
•	int StoreInt(int nbits, int atBitPos, int from);
•	int StoreUInt(int nbits, int atBitPos, unsigned int from);
•	int StoreUchar(int nbits, int atBitPos, unsigned char from);
•	int StoreULong(int nbits, int atBitPos, unsigned long from);
•	int StoreLong(int nbits, int atBitPos, long from);
•	int StoreFloat(int atBitPos, float from);
•	int StoreDouble(int atBitPos, double from);



RETRIEVING REGULAR TYPED DATA FROM CHUNKS OF BIT ARRAY
Compacted data can be retrieved as a whole byte array:
•	unsigned char* GetByteArray();
Or can be retrieved individually and copy to a regular typed variable:
•	int BitArray::Bit(int atBitPos, bool* b);
•	int Retrieve(int nbits, int atBitPos, int* toInt);
•	int Retrieve(int nbits, int atBitPos, char* toChar);
•	int Retrieve(int nbits, int atBitPos, unsigned int* toUint);
•	int Retrieve(int nbits, int atBitPos, unsigned long* toUlong);
•	int Retrieve(int nbits, int atBitPos, long* toLong);
•	int RetrieveFloat(int atBitPos, float* toFloat);
•	int RetrieveDouble(int atBitPos, double* toDouble);

EXAMPLES IN C++

The following lines of codes show how to store and retrieve various types of data into a bit array not aligned on bytes
const int length = 128;
unsigned char byteArray[4]{ 0x45, 0x72, 0x78, 0x7 };
bool b1, b2, b3, b4, b5, b6, b7;
int i1, i2, i3, i4;
unsigned char c1;
float f1;
long l1;
// Declare the 1024 bits array (128 bytes)
BitArray bitArray(length);

// Store 

bitArray.SetBit(0, true); // set true at bit b0
bitArray.SetBit(1, false); // set false at b1
bitArray.SetBit(2, true); // set true at b2
bitArray.StoreInt(6, 3, 37); //store 6 first bits from int = 37 starting bit3 (to bit8)
bitArray.StoreFloat(9, (float)46.582842); // store the float starting b9 (to bit40)
bitArray.StoreChar(8, 41, 255); // etc…
bitArray.StoreLong(32, 49, 46582842);
bitArray.StoreInt(4, 81, 14);
bitArray.SetBit(85, true);
bitArray.SetBit(86, true);
bitArray.SetBit(87, true);
bitArray.StoreInt(4, 88, 13);
bitArray.SetBit(92, true);
bitArray.StoreBits(31, 0, 93, byteArray, sizeof(byteArray)/sizeof(char));
bitArray.StoreInt(4, 124, 12);

// Retrieve
bitArray.Bit(0, &b1);// Retrieve b0 into bool b1
bitArray.Bit(1, &b2); 
bitArray.Bit(2, &b3);
bitArray.RetrieveInt(6, 3, &i1); // Retrieve 6 bits at b3 and assign value to int i1
bitArray.RetrieveFloat(9, &f1); // Retrieve float f1 from bits starting at b9
bitArray.RetrieveChar(8, 41, &c1);
bitArray.RetrieveLong(32, 49, &l1);
bitArray.RetrieveInt(4, 81, &i2);
bitArray.Bit(85, &b4);
bitArray.Bit(86, &b5);
bitArray.Bit(87, &b6);
bitArray.RetrieveInt(4, 88, &i3);
bitArray.Bit(92, &b7);
bitArray.RetrieveByteArray(31, 93, byteArray, sizeof(byteArray));
bitArray.RetrieveInt(4, 124, &i4);


EXAMPLES IN C#
           const int length = 128;

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
