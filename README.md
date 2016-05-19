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

