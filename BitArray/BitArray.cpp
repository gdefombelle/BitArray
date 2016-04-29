#include "stdafx.h"
#include "BitArray.h"
#include <stdlib.h>
#include <bitset>


// 32 bits+  basic type length


BitArray::BitArray(int bitSize)
{
	// int a = (dividend + (divisor - 1)) / divisor;
	byteArrayCount = ((bitSize + 7) / 8);
	byteArray = (unsigned char*)calloc(byteArrayCount, sizeof(char));
	Initialize();
}


BitArray::~BitArray()
{
}

// ******************* Store ************************************

int BitArray::SetBit(int atBitPos, bool b) {
	if (atBitPos > byteArrayCount * sizeof(char)) return false;
	if (b) byteArray[atBitPos / 8] |= (1 << (atBitPos % 8));
	else byteArray[atBitPos / 8] &= ~(1 << (atBitPos % 8));
	return true;
}
int BitArray::Toggle(int atBitPos, bool *b) {
	if (atBitPos > byteArrayCount * sizeof(char)) return false;
	byteArray[atBitPos / 8] ^= (1 << (atBitPos % 8));
	*b = byteArray[atBitPos / 8] & (1 << (atBitPos % 8));
	return true;
}
int BitArray::StoreInt(int nbits, int atBitPos, int value) {
	if (nbits > sizeof(int) * 8) return false;
	if (value > (1 << nbits)) return false;
	intToByteArray(value);
	return StoreBits(nbits, 0, atBitPos, _baInt, BIG_ENDIAN);
}
int BitArray::StoreUInt(int nbits, int atBitPos, unsigned int value) {
	if (nbits > sizeof(int) * 8) return false;
	if (value > (1 << nbits)) return false;
	intToByteArray(value);
	return StoreBits(nbits, 0, atBitPos, _baInt, BIG_ENDIAN);
}

int BitArray::StoreChar(int nbits, int atBitPos, unsigned char value) {
	if (nbits > sizeof(char) * 8) return false;
	if (value > (1 << nbits)) return false;
	charToByteArray(value);
	return StoreBits(nbits, 0, atBitPos, _baChar, BIG_ENDIAN);
}
int BitArray::StoreLong(int nbits, int atBitPos, long value) {
	if (nbits > sizeof(long) * 8) return false;
	if (value > (1 << nbits)) return false;
	longToByteArray(value);
	return StoreBits(nbits, 0, atBitPos, _baLong, BIG_ENDIAN);
}
int BitArray::StoreULong(int nbits, int atBitPos, unsigned long value) {
	if (nbits > sizeof(long) * 8) return false;
	if (value > (1 << nbits)) return false;
	longToByteArray(value);
	return StoreBits(nbits, 0, atBitPos, _baLong, BIG_ENDIAN);
}

int BitArray::StoreFloat(int atBitPos, float value) {
	int len = sizeof(float);
	if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
	union {
		float af;
		unsigned char bytes[sizeof(float)];
	} u;
	u.af = value;
	return StoreBits(len * 8, 0, atBitPos, u.bytes, IsBigEndian() ? BIG_ENDIAN : LITTLE_ENDIAN);
}

int BitArray::StoreDouble(int atBitPos, double value) {
	int len = sizeof(double);
	if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
	union {
		double af;
		unsigned char bytes[sizeof(double)];
	} u;
	u.af = value;
	return StoreBits(len * 8, 0, atBitPos, u.bytes, IsBigEndian() ? BIG_ENDIAN : LITTLE_ENDIAN);
}


int BitArray::StoreBits(int nbits, int fromSourceStartingBit, int atTargetStartingBit, unsigned char value[], ENDIAN endian) {
	// nbits: number of bits to store
	// startingBit index zero based of the first bit to update within the bit array
	// value[] byte array holding the value

	int ret = true;
	//preliminary checks
	//if (nbits > sizeof(value) * sizeof(char) * 8) return 2;
	if (atTargetStartingBit + nbits > byteArrayCount * 8) return 3;
	//if (fromSourceStartingBit + nbits > sizeof(value) * sizeof(char) * 8) return 5;
	//
	// convert byte array to LITTLE_ENDIAN
	if (endian == BIG_ENDIAN) value = reverseByteArray(value);

	int sourceEndingByte = (fromSourceStartingBit + nbits) / 8 - 1;
	int sourceEndingBit = fromSourceStartingBit + nbits - 1;
	int targetEndingBit = nbits + atTargetStartingBit - 1;
	int targetStartingByte = atTargetStartingBit / 8;
	int targetEndingByte = (targetEndingBit) / 8;

	int currentTargetByte = targetStartingByte;


	int cursorTargetGlobalBit = atTargetStartingBit;
	int cursorSourceGlobalBit = fromSourceStartingBit;


	while (cursorSourceGlobalBit < sourceEndingBit) {
		int cursorSourceLocalBit = cursorSourceGlobalBit % 8;
		int cursorTargetLocalBit = cursorTargetGlobalBit % 8;
		int cursorTargetByte = cursorTargetGlobalBit / 8;
		int currentSourceByte = cursorSourceGlobalBit / 8;
		int bitPacketSize = MIN(sourceEndingBit - cursorSourceGlobalBit + 1, MIN(7 - cursorSourceLocalBit + 1, 7 - cursorTargetLocalBit + 1));
		InsertBitsFromByteToByte(value[currentSourceByte], cursorSourceLocalBit, cursorTargetByte, cursorTargetLocalBit, bitPacketSize);
		cursorSourceGlobalBit += bitPacketSize;
		cursorTargetGlobalBit += bitPacketSize;
	}

	return ret;
}

int BitArray::StoreBits2(int nbits, int fromStartingBit, int atStartingBit, unsigned char value[], ENDIAN endian) {

	return true;
}
// ***************** Retrieve **********************************
int BitArray::Bit(int atBitPos, bool *b) {
	if (atBitPos > byteArrayCount * sizeof(char)) return -1;
	*b = (byteArray[atBitPos / 8] & (1 << (atBitPos % 8)));
	return true;
}

int BitArray::Retrieve(int nbits, int atBitPos, unsigned char *buffer, int len, ENDIAN endian) {
	if (nbits > len * sizeof(char) * 8) return -1;
	for (int i = 0; i < len; i++) buffer[i] = 0;

	int cursorBuffer = 0;
	for (int i = atBitPos; i < atBitPos + nbits; i++) {
		bool b = byteArray[i / 8] & (1 << (i % 8));
		if (b) buffer[cursorBuffer / 8] |= (1 << (cursorBuffer % 8));
		else buffer[cursorBuffer / 8] &= ~(1 << (cursorBuffer % 8));
		cursorBuffer++;
	}
	if (endian == BIG_ENDIAN) buffer = reverseByteArray(buffer, len);
	return true;
}

int BitArray::Retrieve(int nbits, int atBitPos, int* toInt) {
	int len = sizeof(int);
	if (nbits> len * 8) return -1;
	*toInt = 0;
	for (int i = atBitPos; i < atBitPos + nbits; i++)
		*toInt |= (int)GetBit(i) << (i - atBitPos);
}

int BitArray::Retrieve(int nbits, int atBitPos, char* toChar) {
	if (nbits >  sizeof(char) * 8) return -1;
	for (int i = atBitPos; i < atBitPos + nbits; i++)
		*toChar |= (int)GetBit(i) << (i - atBitPos);
}

int BitArray::Retrieve(int nbits, int atBitPos, unsigned int* toUint) {
	return BitArray::Retrieve(nbits, atBitPos, (int*)toUint);
}
int BitArray::Retrieve(int nbits, int atBitPos, unsigned long* toUlong) {
	int len = sizeof(long);
	if (nbits> len * 8) return -1;
	*toUlong = 0;
	for (int i = atBitPos; i < atBitPos + nbits; i++)
		*toUlong |= (int)GetBit(i) << (i - atBitPos);
}
int BitArray::Retrieve(int nbits, int atBitPos, long* toLong) {
	return BitArray::Retrieve(nbits, atBitPos, (unsigned long*)toLong);
}

int BitArray::Retrieve(int atBitPos, float* toFloat) {
	int len = sizeof(float);
	if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
	union {
		float f;
		char bytes[sizeof(float)];
	} u;
	unsigned char* buffer = (unsigned char*)calloc(len, sizeof(char));
	Retrieve(len * 8, atBitPos, buffer, len, IsBigEndian() ? BIG_ENDIAN : LITTLE_ENDIAN);
	for (int i = 0; i < sizeof(u.bytes) / sizeof(char); i++) u.bytes[i] = buffer[i];
	*toFloat = u.f;
	return true;
}

int BitArray::Retrieve(int atBitPos, double* toDouble) {
	int len = sizeof(double);
	if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
	union {
		double d;
		char bytes[sizeof(double)];
	} u;
	unsigned char* buffer = (unsigned char*)calloc(len, sizeof(char));
	Retrieve(len * 8, atBitPos, buffer, len, IsBigEndian() ? BIG_ENDIAN : LITTLE_ENDIAN);
	for (int i = 0; i < sizeof(u.bytes) / sizeof(char); i++) u.bytes[i] = buffer[i];
	*toDouble = u.d;
	return true;
}



// ******** private methods   *********************************
void BitArray::Initialize() {
	for (int i = 0; i < byteArrayCount; i++) {
		byteArray[i] = 0;
	}
}

unsigned char BitArray::OneByteMask(int from, int to) {
	unsigned char r = 0;
	for (int i = from; i <= to; i++)
		r |= 1 << i;
	return r;
}
int BitArray::GetBit(int atPos) {
	unsigned char c = (byteArray[atPos / 8] & (1 << (atPos % 8)));
	return (c == 0 ? 0 : 1);
}

void BitArray::InsertBitsFromByteToByte(unsigned char sourceByte, int sourceBitStartIndex, int targetByteIndex, int targetBitStartIndex, int nbits) {
	unsigned char valueToInsert;
	valueToInsert = OneByteMask(sourceBitStartIndex, sourceBitStartIndex + nbits - 1) & sourceByte;
	valueToInsert = valueToInsert >> sourceBitStartIndex;
	valueToInsert = valueToInsert << targetBitStartIndex;
	unsigned char mask2 = ~OneByteMask(targetBitStartIndex, targetBitStartIndex + nbits - 1);
	byteArray[targetByteIndex] = byteArray[targetByteIndex] & mask2;
	byteArray[targetByteIndex] = byteArray[targetByteIndex] | valueToInsert;
}

unsigned char* BitArray::reverseByteArray(unsigned char byteArray[]) {
	int l = sizeof(byteArray);
	unsigned char* _v = (unsigned char*)malloc(l * sizeof(char));
	for (int i = 0; i < l; i++) _v[l - i - 1] = byteArray[i];
	return _v;
}
unsigned char* BitArray::reverseByteArray(unsigned char *byteArray, int len) {
	unsigned char* _v = (unsigned char*)malloc(len * sizeof(char));
	for (int i = 0; i < len; i++) _v[len - i - 1] = byteArray[i];
	return _v;
}

unsigned char* BitArray::GetByteArray(ENDIAN endian = BIG_ENDIAN) {
	if (BIG_ENDIAN) return reverseByteArray(byteArray);
	else return byteArray;
}

int BitArray::GetByteArrayCount() {
	return byteArrayCount;
}

void BitArray::intToByteArray(unsigned int n) {
	int l = sizeof(int);
	for (int i = l - 1; i >= 0; i--) {
		_baInt[l - i - 1] = (n >> 8 * i) & 0xFF;
	}
}
void BitArray::longToByteArray(unsigned int n) {
	int l = sizeof(long);
	for (int i = l - 1; i >= 0; i--) {
		_baLong[l - i - 1] = (n >> 8 * i) & 0xFF;
	}
}

void BitArray::charToByteArray(unsigned char n) {
	int l = sizeof(char);
	for (int i = l - 1; i >= 0; i--) {
		_baChar[l - i - 1] = (n >> 8 * i) & 0xFF;
	}
}

bool BitArray::IsBigEndian(void)
{
	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };
	return bint.c[0] == 1;
}