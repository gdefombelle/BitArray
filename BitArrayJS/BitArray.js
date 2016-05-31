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

    _baChar = new Uint8Array(1);
    _baInt = new Uint8Array(4);
    _baLong = new Uint8Array(8);
    // 2 power 32 was deliberately changed to 2 32 -1 () power to be contained in 32-bit
    _power2 = new Uint32Array([1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967295]);
    byteArrayCount = 0;
    byteArray = null;

    if (byteArray) {
        this.byteArray = byteArray;
        this.byteArrayCount = byteArray.length;
    }
    else {
        if (bitSize) {
            this.byteArrayCount = Math.floor(((bitSize + 7) / 8));
            this.byteArray = new Uint8Array(byteArrayCount);
        }
        else {
            alert("invalid ByteArray initialization");
            return null;
        }
    }

    function forwardCursor(nbits) {
        var _cursor = 0;
        function inc() {
            _cursor += nbits;
            return _cursor;
        }
        return inc();
    }

    function isAvailableRoom(nbits){
        return this.forwardCursor(0) + nbits <= (byteArrayCount * 8);
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
    
    setBit = function (atBitPos, value) {
        atBitPos = parseInt(atBitPos);
        if (atBitPos > byteArrayCount * 1 * 8) return 0;
        if (value) this.byteArray[Math.floor(atBitPos / 8)] |= (1 << (atBitPos % 8));
        else this.byteArray[Math.floor(atBitPos / 8)] &= (~(1 << (atBitPos % 8)));
        forwardCursor(1);
        return true;
    }
    toggleBit = function (atBitPos, value) {
        if (atBitPos > byteArrayCount * 1) return 0;
        this.byteArray[Math.floor(atBitPos / 8)] ^= (byte)(1 << (atBitPos % 8));
        b = (this.byteArray[Math.floor(atBitPos / 8)] & (1 << (atBitPos % 8))) != 0;
        return true;
    }
    storeByte = function (nbits, atBitPos, value) {
        atBitPos = parseInt(atBitPos);
        nbits = parseInt(nbits);
        value = parseInt(value);
        if (nbits > 1 * 8) return 0;
        if (value >= _power2[nbits]) return -1;
        var bytes = new Uint8Array([value]);
        return storeBits(nbits, 0, atBitPos, bytes);
    }
    storeInt = function (nbits, atBitPos, value) {
        atBitPos = parseInt(atBitPos);
        nbits = parseInt(nbits);
        value = parseInt(value);
        if (nbits > 4 * 8) return 0;
        if (value >= _power2[nbits]) return -1;
        // negative value cannot be truncated (yet)
        if (value < 0 && nbits != 4 * 8) return -2;
        var bytes = new Uint8Array([0, 0, 0, 0]);
        var x = value;
        for ( var index = 0; index < bytes.length; index ++ ) {
            var byte = x & 0xff;
            bytes [ index ] = byte;
            x = (x - byte) / 256 ;
        }
        return storeBits(nbits, 0, atBitPos, bytes);
    }

    storeLong = function (nbits, atBitPos, value) {
        atBitPos = parseInt(atBitPos);
        nbits = parseInt(nbits);
        value = parseInt(value);
        if (nbits > 8 * 8) return 0;
        // negative value cannotbe truncated
        if (value < 0 && nbits != 8 * 8) return -2;
        // check for possible overflow
        if (value >= _power2[nbits - 1]) return -1;
        var bytes = new Uint8Array([0, 0, 0, 0, 0, 0, 0, 0]);
        var x = value;
        for (var index = 0; index < bytes.length; index++) {
            var byte = x & 0xff;
            bytes[index] = byte;
            x = (x - byte) / 256;
        }
        return storeBits(nbits, 0, atBitPos, bytes);
    };

    storeFloat = function (atBitPos, value) {
        atBitPos = parseInt(atBitPos);
        value = parseFloat(value);

        len = 4;
        if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
        var far = new Float32Array(1);
        far[0] = value;
        var bytes = new Uint8Array(far.buffer);
        return storeBits(len * 8, 0, atBitPos, bytes);
    }

    function storeDouble(atBitPos, value) {
        len = sizeof(double);
        if (len * 8 + atBitPos - 1 > byteArrayCount * 8) return -1;
        var far = new Float64Array(1);
        far[0] = value;
        var bytes = new Uint8Array(far.buffer);
        return storeBits(len * 8, 0, atBitPos, bytes);
    }

    storeBits = function (nbits, fromSourceStartingBit, atTargetStartingBit, value){
        if (Object.prototype.toString.call(value) != "[object Uint8Array]") return -2;
        ret = 1;
        if (atTargetStartingBit + nbits > (byteArrayCount * 8)) return 3;
        //if (fromSourceStartingBit + nbits > sizeof(value) * 1 * 8) return 5;
        //
        // convert byte array to LITTLE_ENDIAN
        if (BIG_ENDIAN()) value = ReverseByteArray(value);

        sourceEndingByte = Math.max((fromSourceStartingBit + nbits) / 8 - 1, 0);
        sourceEndingBit = Math.max(fromSourceStartingBit + nbits - 1,0);
        targetEndingBit = Math.max(nbits + atTargetStartingBit - 1,0);
        targetStartingByte = Math.floor(atTargetStartingBit / 8);
        targetEndingByte = Math.floor((targetEndingBit) / 8);

        currentTargetByte = targetStartingByte;


       cursorTargetGlobalBit = atTargetStartingBit;
       cursorSourceGlobalBit = fromSourceStartingBit;


        while (cursorSourceGlobalBit <= sourceEndingBit)
        {
           cursorSourceLocalBit = cursorSourceGlobalBit % 8;
           cursorTargetLocalBit = cursorTargetGlobalBit % 8;
           cursorTargetByte = Math.floor(cursorTargetGlobalBit / 8);
           currentSourceByte = Math.floor(cursorSourceGlobalBit / 8);
           bitPacketSize = Math.min(sourceEndingBit - cursorSourceGlobalBit + 1, Math.min(7 - cursorSourceLocalBit + 1, 7 - cursorTargetLocalBit + 1));
           insertBitsFromByteToByte(value[currentSourceByte], cursorSourceLocalBit, cursorTargetByte, cursorTargetLocalBit, bitPacketSize);
           cursorSourceGlobalBit += bitPacketSize;
           cursorTargetGlobalBit += bitPacketSize;
        }
        // update cursor
        cursor = atTargetStartingBit + nbits;
        return ret;

        function insertBitsFromByteToByte(sourceByte, sourceBitStartIndex,  targetByteIndex, targetBitStartIndex,  nbits)
        {
            var valueToInsert;
            function OneByteMask(from, to){
                var r = 0;
                for (i = from; i <= to; i++)
                    r |= (1 << i);
                return r;
            }

            valueToInsert = (OneByteMask(sourceBitStartIndex, sourceBitStartIndex + nbits - 1) & sourceByte);
            valueToInsert = (valueToInsert >> sourceBitStartIndex);
            valueToInsert = (valueToInsert << targetBitStartIndex);
            mask2 = (~OneByteMask(targetBitStartIndex, targetBitStartIndex + nbits - 1));
            this.byteArray[targetByteIndex] = (this.byteArray[targetByteIndex] & mask2);
            this.byteArray[targetByteIndex] = (this.byteArray[targetByteIndex] | valueToInsert);
        }
 
    }

    // ****************** append ************************
    function appendBit(value) {
        if (isAvailableRoom(1))
            return setBit(forwardCursor(0), value);
        else
            return -1;
    }

    function appendByte(value, nbits) {
        var _nbits = (nbits == undefined || !nbits) ? 1 : nbits;
        if (isAvailableRoom(_nbits)) {
            return storeByte(_nbits, forwardCursor(0), value)
        }
        else
            return -1;
    }

    function appendInt(value, nbits) {
        var _nbits = (nbits == undefined || !nbits) ? 4 : nbits;
        if (isAvailableRoom(_nbits)) {
            return storeInt(_nbits, forwardCursor(0), value)
        }
        else
            return -1;
    }

    function appendLong(value, nbits) {
        var _nbits = (nbits == undefined || !nbits) ? 8 : nbits;
        if (isAvailableRoom(_nbits)) {
            return storeInt(_nbits, forwardCursor(0), value)
        }
        else
            return -1;
    }

    function appendFloat(value) {
        var _nbits = 32;
        if (isAvailableRoom(_nbits)) {
            return storeFloat( forwardCursor(0), value)
        }
        else
            return -1;
    }

    function appendDouble(value) {
        var _nbits = 64;
        if (isAvailableRoom(_nbits)) {
            return storeDouble(forwardCursor(0), value)
        }
        else
            return -1;
    }

    function appendByteArray(value, nbits) {
        var _nbits = (nbits == undefined || !nbits) ? sizeof(value) * 8 : nbits;
        if (isAvailableRoom(_nbits)) {
            return storeBits(nbist,0, (forwardCursor(0), value));
        }
        else
            return -1;
    }
    //******************* Retrieve *********************
    bit = function (atBitPos){
        if (atBitPos > byteArrayCount * 1 * 8) return -1;
        return (this.byteArray[Math.floor(atBitPos / 8)] & (1 << (atBitPos % 8))) !=0;
    }

    function getBit(atPos){
        c = (this.byteArray[Math.floor(atPos / 8)] & (1 << (atPos % 8)));
        return (c == 0 ? 0 : 1);
    }

    retrieveByteArray = function (nbits, atBitPos){
        nbits = parseInt(nbits);
        atBitPos = parseInt(atBitPos);
        cursorBuffer = 0;
        for (i = atBitPos; i < atBitPos + nbits; i++)
        {
            b = (this.byteArray[Math.floor(i / 8)] & (1 << (i % 8)))!=0;
            if (b) buffer[Math.floor(Math.floor(cursorBuffer / 8))] |= (1 << (cursorBuffer % 8));
        else buffer[Math.floor(cursorBuffer / 8)] &= ~(1 << (cursorBuffer % 8));
            cursorBuffer++;
        }
        if (BIG_ENDIAN()) buffer = ReverseByteArray(buffer);
        return buffer;
    }

    retrieveInt = function(nbits, atBitPos)
    {
        nbits = parseInt(nbits);
        atBitPos = parseInt(atBitPos);
        len = 4;
        if (nbits > len * 8) return -1;
        toInt = 0;
        for ( i = atBitPos; i < atBitPos + nbits; i++)
            toInt |= getBit(i) << (i - atBitPos);
        return toInt;
    }
    retrieveLong = function (nbits, atBitPos) {
        nbits = parseInt(nbits);
        atBitPos = parseInt(atBitPos);
        len = 8;
        if (nbits > len * 8) return -1;
        toLong = 0;
        for (i = atBitPos; i < atBitPos + nbits; i++)
            toLong |= getBit(i) << (i - atBitPos);
        return toLong;
    }
    retrieveByte = function (nbits, atBitPos) {
        nbits = parseInt(nbits);
        atBitPos = parseInt(atBitPos);
        len = 1;
        if (nbits > len * 8) return -1;
        toByte = 0;
        for (i = atBitPos; i < atBitPos + nbits; i++)
            toByte |= getBit(i) << (i - atBitPos);
        return toByte;
    }

    retrieveFloat = function (atBitPos) {
        atBitPos = parseInt(atBitPos);
    }

    return this;
}

