/*
 
    Copyright(C) <2016>  <Gabriel J. de Fombelle>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see<http://www.gnu.org/licenses/>.

    my email: gabriel.de.fombelle@gmail.com

*/





function ByteArray(sizeInBytes) {
    byteArray = null;
    BIG_ENDIAN = false; // default is LITTLE_ENDIAN
    _baChar = new Uint8Array(sizeof(char));
    _baInt = new Uint8Array(sizeof(int));
    _baLong = new Uint8Array(sizeof(long));
    // 2 power 32 was deliberately changed to 2 32 -1 () power to be contained in 32-bit
    _power2 = new UInt32Array[1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967295];

    byteArray = new Uint8Array(sizeInBytes);

}