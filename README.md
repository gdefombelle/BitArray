# BitArray
C++ Library to easily store and retrieve bits sequences to and from a, array of bytes 
PROJECT BITARRAY C++ 


GOAL
BitArray is a C/C++  class library specially designed for IoT and embedded software developers to easily compact and retrieve data stored as bit sequences of an arbitrary length (i.e. not necessarily multiple of 8 ) into array of bytes, not aligning data against bytes but bits. BitArray avoid annoying and quite often long programming to do that. The library would be particularly useful in IoT programming for carrying data over low throughput networks such as Ultra Narrow Band networks like Sigfox, LoRa, etc.
Basically BitArray provides methods for 
1.	Simply insert n bits from a source (int, long, float, double, char, bool, byte[]) toward  a BitArray starting at a given bit index. 
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

EXAMPLES

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
bitArray.StoreInt(6, 3, 67); //store 6 first bits from int = 67 starting bit3 (to bit8)
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

