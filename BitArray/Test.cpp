// TestBitArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "BitArray.h"
#include <string.h>
int main()
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
	printf("TEST BITARRAY.\n");

	unsigned char byteArray[4]{ 0x45, 0x72, 0x78, 0x7 };
	bool b1, b2, b3, b4, b5, b6, b7;
	int i1, i2, i3, i4;
	unsigned char c1;
	float f1;
	long l1;
	// Store 
	BitArray bitArray(length);
	bitArray.SetBit(0, true);
	bitArray.SetBit(1, false);
	bitArray.SetBit(2, true);
	bitArray.StoreInt(6, 3, 27);
	bitArray.StoreFloat(9, (float)3.14159);
	bitArray.StoreChar(8, 41, 255);
	bitArray.StoreLong(32, 49, 2231000);
	bitArray.StoreInt(4, 81, 14);
	bitArray.SetBit(85, true);
	bitArray.SetBit(86, true);
	bitArray.SetBit(87, true);
	bitArray.StoreInt(4, 88, 13);
	bitArray.SetBit(92, true);
	bitArray.StoreByteArray(31, 0, 93, byteArray, sizeof(byteArray)/sizeof(char));
	bitArray.StoreInt(4, 124, 12);
	
	// Retrieve
	bitArray.Bit(0, &b1);
	bitArray.Bit(1, &b2);
	bitArray.Bit(2, &b3);
	bitArray.RetrieveInt(6, 3, &i1);
	bitArray.RetrieveFloat(9, &f1);
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
	// Print everything
	printf("b1: %d\n",b1);
	printf("b2: %d\n",b2);
	printf("b3: %d\n",b3);
	printf("i1: %d\n",i1);
	printf("f1: %f\n",f1);
	printf("c1: %d\n",c1);
	printf("l1: %d\n",l1);
	printf("i2: %d\n",i2);
	printf("b4: %d\n",b4);
	printf("b5: %d\n",b5);
	printf("b6: %d\n",b6);
	printf("i3: %d\n",i3);
	// Print bitArray
	unsigned char* buffer;
	buffer = bitArray.GetEntireBitArray();
	int i;
	for (i = 0; i < bitArray.GetBitArraySizeByte(); i++)
	{
		if (i > 0) printf(":");
		printf("%02X", buffer[i]);
	}
	printf("\n");
	
	_getch();
	

	return 0;
}

