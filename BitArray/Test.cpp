// TestBitArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "BitArray.h"
int main()
{
	printf("How long should the dynamic array be? ");

	int length = 96;
	//scanf_s("%d", &length);
	// test class BitArray
	printf("TEST BITARRAY.");
	BitArray bitArray(length);
	printf("length: %d\n", bitArray.GetByteArrayCount());
	//for (int i = 0; i < bitArray.GetByteArrayCount(); i++)
	//	printf("bitArray[%d] = %d, ", i, bitArray.GetByteArray()[i]);
	unsigned char buffer[4]{ 0x7f, 0x12, 0x88, 0xa9 };
	for (int i = 0; i <sizeof(buffer); i++)
		printf("buffer[%d] = %d, ", i, buffer[i]);
	unsigned char v = 0b10101001;
	printf("\nNumber before shifting : %d", v);
	unsigned char mask = bitArray.OneByteMask(1, 3);

	printf("\nmask  : %d", mask);
	printf("\nnot mask  : %d", (unsigned char)~mask);

	bool isBiendian = bitArray.IsBigEndian();
	int errorCode = bitArray.StoreBits(9, 3, 9, buffer, bitArray.BIG_ENDIAN);

	bool b = false;
	bitArray.SetBit(9, true);
	bitArray.Bit(9, &b);
	bitArray.SetBit(9, false);
	bitArray.Bit(9, &b);

	int i = 13;
	bitArray.StoreInt(4, 7, i);
	float f = 32.145787;
	double d = 465478797979.123;
	bitArray.StoreFloat(16, f);
	unsigned char* byteArray = bitArray.GetByteArray(bitArray.BIG_ENDIAN);
	int j = 0;
	int r = -5;
	bitArray.Retrieve(4, 7, &r);
	char c = 0;
	bitArray.Retrieve(4, 7, &c);

	unsigned int u;
	bitArray.Retrieve(4, 7, &u);

	unsigned long ul;
	bitArray.Retrieve(4, 7, &ul);


	unsigned char buffer2[4];
	// JJJJ
	bitArray.Retrieve(4, 7, buffer2, 4, bitArray.BIG_ENDIAN);
	long ll;
	bitArray.Retrieve(4, 7, &ll);


	float f2;
	bitArray.Retrieve(16, &f2);


	bitArray.StoreDouble(3, d);
	unsigned char buffer64[64];
	bitArray.Retrieve(64, 3, buffer64, 64, bitArray.BIG_ENDIAN);

	double d2 = 0;
	bitArray.Retrieve(3, &d2);
	_getch();


	return 0;
}

