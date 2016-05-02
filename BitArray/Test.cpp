// TestBitArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "BitArray.h"
#include <string.h>
int main()
{
	printf("How long should the dynamic array be ? ");

	int length = 96;
	//scanf_s("%d", &length);
	// test class BitArray
	printf("TEST BITARRAY.");
	BitArray bitArray(length);
	printf("length: %d\n", bitArray.GetBitArraySizeByte());

	int i1 = 800;
	bitArray.StoreInt(8, 0, i1);
	float f1 = 3.14616;
	bitArray.StoreFloat(8, f1);

	float f2 = 0;
	int i2 = 0;

	bitArray.RetrieveInt(8, 0, &i2);
	bitArray.RetrieveFloat(8, &f2);


	bool b1 = true;
	bool b2 = false;
	bool b3 = true;
	bool b4;
	bool b5;
	bool b6;

	bitArray.SetBit(40, b1);
	bitArray.SetBit(41, b2);
	bitArray.SetBit(42, b3);

	bitArray.Bit(40, &b4);
	bitArray.Bit(41, &b5);
	bitArray.Bit(42, &b6);

	struct {
		int a;
		float f;
		double d;
		bool c;
		char str[25];
		char* pstr;
	} ss;
	ss.a = 1234;
	ss.f = 3.14154687;
	ss.d = 465446464;
	strcpy_s(ss.str, "C Programming");
	ss.pstr = "bonjour\0";
	_getch();


	return 0;
}

