// Format.h - Declares the formatting functions.
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

#ifndef BIN_DATA_FORMAT_H
#define BIN_DATA_FORMAT_H

#include <cstddef>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <stdexcept>
#include "IntConstants.h"

namespace BinData
{
    /// @brief The width of a hexidecimal octet's string representation.
    constexpr int hexOctetWidth{ 2 };

    /// @brief The character used to separate bytes in bin and hex formats.
    constexpr char byteSeparator{ ' ' };

    /// @brief The character to pad hex values with in an octet. 
    constexpr char hexPadCharacter{ '0' };

    constexpr char nonPrintableReplacement{ '.' };

    /// @brief Determines the beginning of non-printable ASCII values.
    /// @remark The range of standard ASCII values is 0 to 127 as ASCII is a
    /// 7-bit encoding. Some platforms use the extra bit of a character byte
    /// to represent "extended" characters. These characters are often 
    /// represented as positive values (128 - 255), but since the C++ standard
    /// char type is a signed value, they are in the range -128 to -1. The 
    /// characters in this range vary by platform and are not part of the ASCII
    /// standard, thus this library treats them as non-printable characters. 
    constexpr int nonPrintableAsciiBegin{ -128 };

    //constexpr int asciiControlCodeBegin{ 0 };

    //constexpr int asciiControlCodeEnd{ 31 };

    /// @brief Determines the end of non-printable ASCII values.
    /// @remark Within the standard ASCII range of values, the first 32
    /// characters (0 - 31) are non-printable control codes. Thus the end of
    /// the range of both non-standard and standard ASCII non-printable 
    /// characters is 32 and the first printable character is 33.
    constexpr int nonPrintableAsciiEnd{ 31 };


    constexpr int printableAsciiBegin{ 32 };

    /// @brief Determines the non-printable ASCII DEL code value.
    /// @remark The DEL ASCII code 127 is the one exception to the otherwise
    /// contiguous range of non-printable characters. It is also the very
    /// last value of the range of valid ASCII values. Therefore, the end
    /// of the printable ASCII values is 126.
    constexpr int printableAsciiEnd{ 126 };

    enum class Format
    {
        Hex,
        Bin,
        Dec,
        Ascii
    };

    class InvalidFormat : public std::invalid_argument
    {
    public:
        /// @brief Constructs an InvalidInstruction exception.
        /// @param message The error message to include with the exception.
        InvalidFormat(const char* message) : std::invalid_argument(message) { }
    };

    std::string FormatHex(char* data, std::size_t size);

    std::string FormatBin(char* data, std::size_t size);

    std::string FormatAscii(char* data, std::size_t size);
}

#endif