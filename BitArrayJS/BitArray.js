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


function ByteArray(bitSize, byteArray) {
    BIG_ENDIAN = false; // default is LITTLE_ENDIAN
    _baChar = new Uint8Array(sizeof(char));
    _baInt = new Uint8Array(sizeof(int));
    _baLong = new Uint8Array(sizeof(long));
    // 2 power 32 was deliberately changed to 2 32 -1 () power to be contained in 32-bit
    _power2 = new UInt32Array[1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967295];
    byteArrayCount = 0;
    byteArray = null;

    if (byteArray) {
        this.byteArray = byteArray;
        this.byteArrayCount = byteArray.length;
        initialize();
    }
    else {
        if (bitSize) {
            this.byteArrayCount = ((bitSize + 7) / 8);
            this.byteArray = new Uint8Array(byteArrayCount);
        }
        else
            alert("invalid ByteArray initialization");
        initialize();
    }
    function initialize() {
        this.BIG_ENDIAN = isBigEndian();
    }
    function forwardCursor(nbits) {
        var _cursor = 0;
        function inc() {
            _cursor += nbits;
            return _cursor;
        }
        return inc();
    }

    function isAvailableRoom(nbist){

    }

    function BIG_ENDIAN() {
        var _bigEndian = null;
        function isBigEndian() {
            var b = new ArrayBuffer(4);
            var a = new Uint32Array(b);
            var c = new Uint8Array(b);
            a[0] = 0xdeadbeef;
            if (c[0] == 0xef) return false;
            if (c[0] == 0xde) return true;
            throw new Error('unknown endianness');
        }
        if (!_bigEndian) { _bigEndian = isBigEndian(); }
        return _bigEndian;
    }
    // ******************* Store ************************
    
    function setBit(atBitPos, value) {
        if (atBitPos > byteArrayCount * sizeof(byte) * 8) return 0;
        if (b) byteArray[atBitPos / 8] |=(byte) (1 << (atBitPos % 8));
        else byteArray[atBitPos / 8] &= (byte)(~(1 << (atBitPos % 8)));
        forwardCursor(1);
        return true;
    }
    function toggleBit(atBitPos, value) {
        if (atBitPos > byteArrayCount * sizeof(byte)) return 0;
        byteArray[atBitPos / 8] ^= (byte)(1 << (atBitPos % 8));
        b = (byteArray[atBitPos / 8] & (1 << (atBitPos % 8))) !=0;
        return true;
    }
    function storeInt(nbits, atBitPos, value) {
        if (nbits > sizeof(int) * 8) return 0;
        if (value >= _power2[nbits]) return -1;
        // negative value cannotbe truncated (yet)
        if (value < 0 && nbits != sizeof(int) * 8) return -2;
        var bytes = [0, 0, 0, 0];
        var x = value;
        for ( var index = 0; index < bytes.length; index ++ ) {
            var byte = x & 0xff;
            bytes [ index ] = byte;
            x = (x - byte) / 256 ;
        }
        return StoreBits(nbits, 0, atBitPos, bytes);
    }

    function storeByte(nbits, atBitPos, value) {
        if (nbits > sizeof(byte) * 8) return 0;
        if (value >= _power2[nbits]) return -1;
        var bytes = [value];
        return StoreBits(nbits, 0, atBitPos, bytes);
    }

    function storeLong(nbist, atBitPos, value) {
        if (nbits > sizeof(long) * 8) return 0;
        // negative value cannotbe truncated
        if (value < 0 && nbits != sizeof(long) * 8) return -2;
        // check for possible overflow
        if (value >= _power2[nbits - 1]) return -1;
        var bytes = [0, 0, 0, 0, 0, 0, 0, 0];
        var x = value;
        for (var index = 0; index < bytes.length; index++) {
            var byte = x & 0xff;
            bytes[index] = byte;
            x = (x - byte) / 256;
        }
        return StoreBits(nbits, 0, atBitPos, bytes);
    };

    function storeFloat(atBitPos, value) {
        len = sizeof(float);
        if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
        var far = new Float32Array(1);
        far[0] = value;
        var bytes = UInt8Array(far.buffer);
        return StoreBits(len * 8, 0, atBitPos, bytes);
    }

    function storeDouble(atBitPos, value) {
        len = sizeof(double);
        if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
        var far = new Float64Array(1);
        far[0] = value;
        var bytes = UInt8Array(far.buffer);
        return StoreBits(len * 8, 0, atBitPos, bytes);
    }

    // ****************** Append ************************
    function AppendBit(value) {

    }

}

