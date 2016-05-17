#pragma once

#ifndef bitArray_h
#define bitArray_h
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
class BitArray
{

public:
	BitArray(int bitSize);

	//store
	~BitArray();
	int StoreBits(int nbits, int fromStartingBit, int atStartingBit, unsigned char from[], int length);
	int SetBit(int atBitPos, bool b);
	int ToggleBit(int atBitPos, bool *b);
	int StoreInt(int nbits, int atBitPos, int from);
	int StoreUInt(int nbits, int atBitPos, unsigned int from);
	int StoreChar(int nbits, int atBitPos, unsigned char from);
	int StoreLong(int nbits, int atBitPos, long from);
	int StoreULong(int nbits, int atBitPos, unsigned long from);
	int StoreFloat(int atBitPos, float from);
	int StoreDouble(int atBitPos, double from);

	// retrieve
	int Bit(int atBitPos, bool* b);
	int RetrieveByteArray(int nbits, int atBitPos, unsigned char *buffer, int len);
	int RetrieveInt(int nbits, int atBitPos, int* toInt);
	int RetrieveChar(int nbits, int atBitPos, unsigned char* toChar);
	int RetrieveUInt(int nbits, int atBitPos, unsigned int* toUint);
	int RetrieveLong(int nbits, int atBitPos, long* toLong);
	int RetrieveULong(int nbits, int atBitPos, unsigned long* toLong);
	int RetrieveFloat(int atBitPos, float* toFloat);
	int RetrieveDouble(int atBitPos, double* toDouble);

	unsigned char* GetEntireBitArray();
	int GetBitArraySizeByte();
	bool IsBigEndian(void);

private:
	void Initialize();
	unsigned char* ReverseByteArray(unsigned char byteArray[]);
	unsigned char* ReverseByteArray(unsigned char *byteArray, int len);
	void InsertBitsFromByteToByte(unsigned char sourceByte, int sourceBitStartIndex, int targetByteIndex, int targetBitStartIndex, int nbits);
	int GetBit(int atPos);
	bool BIG_ENDIAN = false; // default is LITTLE_ENDIAN
	unsigned char *byteArray;
	int byteArrayCount;
	unsigned char OneByteMask(int from, int to);
	void LongToByteArray(unsigned long n);
	void IntToByteArray(unsigned int n);
	void CharToByteArray(unsigned char n);
	unsigned char _baChar[sizeof(char)];
	unsigned char _baInt[sizeof(int)];
	unsigned char _baLong[sizeof(long)];
	// 2 power 32 was deliberately changed to 2 32 -1 () power to be contained in 32-bit
	unsigned long _power2[33]{1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576, 
		2097152,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 ,2147483648 ,4294967295 };

};


#endif