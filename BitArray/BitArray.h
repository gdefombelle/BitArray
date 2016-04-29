#pragma once

#ifndef bitArray_h
#define bitArray_h

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
class BitArray
{

public:
	enum ENDIAN { BIG_ENDIAN, LITTLE_ENDIAN };
	BitArray(int bitSize);
	~BitArray();
	//*** main method 
	int StoreBits(int nbits, int fromStartingBit, int atStartingBit, unsigned char from[], ENDIAN endian);
	int StoreBits2(int nbits, int fromStartingBit, int atStartingBit, unsigned char from[], ENDIAN endian);

	int SetBit(int atBitPos, bool b);
	int Toggle(int atBitPos, bool *b);
	int StoreInt(int nbits, int atBitPos, int from);
	int StoreUInt(int nbits, int atBitPos, unsigned int from);
	int StoreChar(int nbits, int atBitPos, unsigned char from);
	int StoreULong(int nbits, int atBitPos, unsigned long from);
	int StoreLong(int nbits, int atBitPos, long from);
	int StoreFloat(int atBitPos, float from);
	int StoreDouble(int atBitPos, double from);


	int Bit(int atBitPos, bool* b);
	int Retrieve(int nbits, int atBitPos, unsigned char *buffer, int len, ENDIAN endian);

	int Retrieve(int nbits, int atBitPos, int* toInt);
	int Retrieve(int nbits, int atBitPos, char* toChar);
	int Retrieve(int nbits, int atBitPos, unsigned int* toUint);
	int Retrieve(int nbits, int atBitPos, unsigned long* toUlong);
	int Retrieve(int nbits, int atBitPos, long* toLong);
	int Retrieve(int atBitPos, float* toFloat);
	int Retrieve(int atBitPos, double* toDouble);

	unsigned char* GetByteArray(ENDIAN endian);
	int GetByteArrayCount();
	unsigned char OneByteMask(int from, int to);
	bool IsBigEndian(void);
private:
	void Initialize();
	unsigned char* reverseByteArray(unsigned char byteArray[]);
	unsigned char* reverseByteArray(unsigned char *byteArray, int len);
	void InsertBitsFromByteToByte(unsigned char sourceByte, int sourceBitStartIndex, int targetByteIndex, int targetBitStartIndex, int nbits);
	int GetBit(int atPos);

	// Byte array hold the bit set - it is LITTLE ENDIAN - ex FA021BC7:?
	// b[0] = C7; b[1] = 1B; b[2] = 02; b[3] = FA
	unsigned char *byteArray;
	int byteArrayCount;

	int zeroMask = 0b00000000;
	void intToByteArray(unsigned int n);
	void longToByteArray(unsigned int n);
	void charToByteArray(unsigned char n);

	unsigned char _baChar[sizeof(char)];
	unsigned char _baInt[sizeof(int)];
	unsigned char _baLong[sizeof(long)];
};

#endif