// Format.cpp - Defines the formatting functions.
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

#include "Format.h"

namespace BinData
{
    std::string FormatHex(char* data, std::size_t size)
    {
        const auto lastByteIndex = size - 1;
        std::stringstream hexStream;
        for (std::size_t i = 0; i < size; i++)
        {
            // First cast to unsigned so we don't carry a negative value
            unsigned char u = static_cast<unsigned char>(data[i]);

            // Then store the unsigned char value in an integer so the 
            // stringstream captures the numeric value instead of ASCII
            unsigned int byte = u;

            hexStream << std::hex << std::setw(hexOctetWidth)
                << std::setfill(hexPadCharacter) << byte;

            // Don't insert an extra separator if we're at the end
            if (i != lastByteIndex)
                hexStream << byteSeparator;
        }
        
        auto hex = hexStream.str();
        std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
        return hex;
    }

    std::string FormatBin(char* data, std::size_t size)
    {
        const auto lastByteIndex = size - 1;
        std::stringstream binStream;
        for (std::size_t i = 0; i < size; i++)
        {
            // We cannot put a signed char into a bitset without first casting
            // to unsigned long long
            auto byte = static_cast<unsigned long long>(data[i]);

            // The bitset streams the byte as a string representation of binary
            binStream << std::bitset<bitsPerByte>{ byte };

            // Don't insert an extra separator if we're at the end
            if (i != lastByteIndex)
                binStream << byteSeparator;
        }
        return binStream.str();
    }

    std::string FormatAscii(char* data, std::size_t size)
    {
        std::stringstream asciiStream;
        for (std::size_t i = 0; i < size; i++)
        {
            if (data[i] < printableAsciiBegin || data[i] > printableAsciiEnd)
                asciiStream << nonPrintableReplacement;
            else
                asciiStream << data[i];
        }
        return asciiStream.str();
    }
}