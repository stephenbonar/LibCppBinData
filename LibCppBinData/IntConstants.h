// IntConstants.h - Declares integer field constants, like min an max values.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissionsand
// limitations under the License.

#ifndef INT_CONSTANTS_H
#define INT_CONSTANTS_H

namespace BinData
{
    // The long datatype is guaranteed by the standard to be at least 32-bits
    // so we use long to represent the max values of all fields under 32-bits.

    constexpr long minUInt8{ 0 };

    //  2^8 - 1 = 255
    constexpr long maxUInt8{ 255 }; 

    // -2^7 = -128
    constexpr long minInt8{ -128 }; 

    //  2^7 - 1 = 127
    constexpr long maxInt8{ 127 };  


    constexpr long minUInt16{ 0 };

    //  2^16 - 1 = 65535
    constexpr long maxUInt16{ 65535 }; 

    // -2^15 = -32768
    constexpr long minInt16{ -32768 };

    //  2^15 - 1 = 32767
    constexpr long maxInt16{ 32767 };  


    constexpr long minUInt24{ 0 };

    //  2^24 - 1 = 16777215
    constexpr long maxUInt24{ 16777215 };

    // -2^23 = -8388608
    constexpr long minInt24{ -8388608 };

    //  2^23 - 1 = 8388607 
    constexpr long maxInt24{ 8388607 };   

    // The long long datatype is guaranteed by the standard to be at least 
    // 64-bits so we use long long to represent max values of all fields under
    // 64-bits. The one exception is maxUInt64, which can only be guaranteed
    // not to overflow on any platform if it is unsigned. All other mins and
    // maxes are signed for consistency and to reduce possible sign conversion
    // errors.

    constexpr long long minUInt32{ 0LL };

    //  2^32 - 1 = 4294967295
    constexpr long long maxUInt32{ 4294967295LL };

    // -2^32 = -2147483648
    constexpr long long minInt32{ -2147483648LL };

    //  2^32 - 1 = 2147483647
    constexpr long long maxInt32{ 2147483647LL };   


    constexpr long long minUInt64{ 0LL };

    //  2^64 - 1 = 18446744073709551615. Note: We can't use the decimal literal
    // with 64-bit signed integer due to compiler limitations, so we use
    // the hex literal instead.
    constexpr unsigned long long maxUInt64{ 0xFFFFFFFFFFFFFFFFULL };

    //  2^63 - 1 = 9223372036854775807
    constexpr long long maxInt64{ 9223372036854775807LL };

    // -2^63 = -9223372036854775808. Note: due to limitations with sign
    // promotion rules, we can't even use hex to represent the minimum
    // signed value here. Instead, we can take a negative maxInt64 and 
    // subtract 1 from it to circumvent issues with large literals.
    // Note: this is what some implementations of LLONG_MIN in <climits> do
    // to work around the issue as well. Why not just luse LLONG_MIN? 
    // Because on some implementations, long long may be 128 bit instead of
    // 64-bit. This is why we are defining our own constants here. 
    constexpr long long minInt64{ -maxInt64 - 1LL }; 

    constexpr unsigned int bitsPerByte = 8;

    constexpr unsigned char signBitMask{ 0x80 };
}

#endif