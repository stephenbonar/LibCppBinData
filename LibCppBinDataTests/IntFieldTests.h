// IntegrationTests.h - Declares the IntFieldTests class.
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

#ifndef INT_FIELD_TESTS_H
#define INT_FIELD_TESTS_H

#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include <cstring>
#include <string>
#include "IntField.h"
#include "Format.h"

constexpr unsigned int uInt8Val{ 42 };
constexpr int int8Val{ -42 };
constexpr unsigned int uInt16Val{ 4200 };
constexpr int int16Val{ -4200 };
constexpr unsigned long uInt24Val{ 420000 };
constexpr long int24Val{ -420000 };
constexpr unsigned long uInt32Val{ 42000000 };
constexpr long int32Val{ -42000000 };
constexpr unsigned long long uInt64Val{ 420000000000ULL };
constexpr long long int64Val{ -420000000000LL };

const char* uInt8Dec{ "42" };
const char* int8Dec{ "-42" };
const char* uInt16Dec{ "4200" };
const char* int16Dec{ "-4200" };
const char* uInt24Dec{ "420000" };
const char* int24Dec{ "-420000" };
const char* uInt32Dec{ "42000000" };
const char* int32Dec{ "-42000000" };
const char* uInt64Dec{ "420000000000" };
const char* int64Dec{ "-420000000000" };

const char* uInt8Hex{ "2A" };
const char* int8Hex{ "D6" }; 
const char* uInt16Hex{ "68 10" }; 
const char* int16Hex{ "98 EF" }; 
const char* uInt24Hex{ "A0 68 06" };
const char* int24Hex{ "60 97 F9" };
const char* uInt32Hex{ "80 DE 80 02" };
const char* int32Hex{ "80 21 7F FD" };
const char* uInt64Hex{ "00 68 F3 C9 61 00 00 00" };
const char* int64Hex{ "00 98 0C 36 9E FF FF FF" };

const char* uInt16HexBE{ "10 68"};
const char* int16HexBE{ "EF 98" };
const char* uInt24HexBE{ "06 68 A0 " };
const char* int24HexBE{ "F9 97 60"};
const char* uInt32HexBE{ "02 80 DE 80" };
const char* int32HexBE{ "FD 7F 21 80" };
const char* uInt64HexBE{ "00 00 00 61 C9 F3 68 00" };
const char* int64HexBE{ "00 00 00 9E 36 0C 98 00" };

const char* uInt8Bin{ "00101010" }; 
const char* int8Bin{ "11010110" }; 
const char* uInt16Bin{ "01101000 00010000" };
const char* int16Bin{ "10011000 11101111" };
const char* uInt24Bin{ "10100000 01101000 00000110" }; 
const char* int24Bin{ "01100000 10010111 11111001" };
const char* uInt32Bin{ "10000000 11011110 10000000 00000010" };
const char* int32Bin{ "10000000 00100001 01111111 11111101" };
const char* uInt64Bin{ 
    "00000000 01101000 11110011 11001001 01100001 00000000 00000000 00000000"};
const char* int64Bin{ 
    "00000000 10011000 00001100 00110110 10011110 11111111 11111111 11111111"};

const char* uInt16BinBE{ "00010000 01101000" };
const char* int16BinBE{ "11101111 10011000 " };
const char* uInt24BinBE{ "00000110 01101000 10100000 " }; 
const char* int24BinBE{ "11111001 10010111 01100000" };
const char* uInt32BinBE{ "00000010 10000000 11011110 10000000" };
const char* int32BinBE{ "11111101 01111111 00100001 10000000" };
const char* uInt64BinBE{ 
    "00000000 00000000 00000000 01100001 11001001 11110011 01101000 00000000"};
const char* int64BinBE{ 
    "11111111 11111111 11111111 10011110 00110110 00001100 10011000 00000000"};

template<typename FieldType, typename IntType>
class FieldTester
{
public:
    void ExpectCreatedProperly(std::size_t expectedSize)
    {
        FieldType field{};
        EXPECT_EQ(field.Endianness(), BinData::FieldEndianness::Little);
        EXPECT_EQ(field.Size(), expectedSize);
        EXPECT_EQ(field.Value(), 0);
    }

    void ExpectProperValue(std::vector<unsigned char>& rawData, 
        IntType expectedValue)
    {
        FieldType field{};
        ASSERT_EQ(rawData.size(), field.Size());
        std::memcpy(field.Data(), rawData.data(), field.Size());
        EXPECT_EQ(field.Value(), expectedValue);
    }

    void ExpectProperValueBE(std::vector<unsigned char>& rawData, 
        IntType expectedValue)
    {
        FieldType field{};
        field.SetEndianness(BinData::FieldEndianness::Big);
        ASSERT_EQ(rawData.size(), field.Size());
        std::memcpy(field.Data(), rawData.data(), field.Size());
        EXPECT_EQ(field.Value(), expectedValue);
    }

    void ExpectProperString(std::vector<unsigned char>& rawData, 
        std::string expectedString)
    {
        FieldType field{};
        ASSERT_EQ(rawData.size(), field.Size());
        std::memcpy(field.Data(), rawData.data(), field.Size());
        EXPECT_EQ(field.ToString(), expectedString);
    }

    void ExpectProperString(std::vector<unsigned char>& rawData, 
        std::string expectedString, BinData::Format expectedFormat)
    {
        FieldType field{};
        ASSERT_EQ(rawData.size(), field.Size());
        std::memcpy(field.Data(), rawData.data(), field.Size());
        EXPECT_EQ(field.ToString(expectedFormat), expectedString);
    }

    void ExpectValueSetProperly(IntType value)
    {
        FieldType field{};
        ASSERT_NO_THROW(field.SetValue(value));
        EXPECT_EQ(field.Value(), value);
    }

    void ExpectValueSetProperlyBE(std::vector<unsigned char>& rawData, 
        IntType value)
    {
        FieldType field{};
        field.SetEndianness(BinData::FieldEndianness::Big);
        ASSERT_NO_THROW(field.SetValue(value));
        for (int i = 0; i < field.Size(); i++)
            EXPECT_EQ(field.Data()[i], static_cast<char>(rawData[i]));
    }

    void ExpectDeepCopy()
    {
        FieldType f1{};
        f1.SetValue(42);
        FieldType f2{ f1 };
        FieldType f3 = f2;
        EXPECT_NE(f1.Data(), f2.Data());
        EXPECT_NE(f2.Data(), f3.Data());
        EXPECT_EQ(f1.Value(), f2.Value());
        EXPECT_EQ(f2.Value(), f3.Value());
    }

    void ExpectMove()
    {
        FieldType f1{ };
        f1.SetValue(42);
        FieldType f2 = FieldType(std::move(f1));
        EXPECT_THROW(f1.Value(), BinData::InvalidField);
        EXPECT_EQ(f1.Data(), nullptr);
        ASSERT_NE(f2.Data(), nullptr);
        EXPECT_EQ(f2.Value(), 42);
        EXPECT_EQ(f2.Endianness(), BinData::FieldEndianness::Little);
        FieldType f3{ };
        f3 = std::move(f2);
        EXPECT_THROW(f1.Value(), BinData::InvalidField);
        EXPECT_THROW(f2.Value(), BinData::InvalidField);
        EXPECT_EQ(f1.Data(), nullptr);
        EXPECT_EQ(f2.Data(), nullptr);
        ASSERT_NE(f3.Data(), nullptr);
        EXPECT_EQ(f3.Value(), 42);
    }

    void ExpectWritesToStream()
    {
        FieldType f1{ };
        f1.SetValue(42);
        std::stringstream s;
        s << f1;
        EXPECT_EQ(s.str(), f1.ToString());
    }
};

class IntFieldTests : public ::testing::Test
{
protected:
    // [Little Endian Test Values]

    // 42
    std::vector<unsigned char> uInt8Data{ 0x2A }; 

    // -42
    std::vector<unsigned char> int8Data{ 0xD6 };

    // 4200
    std::vector<unsigned char> uInt16Data{ 0x68, 0x10 }; 

    // -4200
    std::vector<unsigned char> int16Data{ 0x98, 0xEF };

    // 420000
    std::vector<unsigned char> uInt24Data{ 0xA0, 0x68, 0x06 }; 

    // -420000
    std::vector<unsigned char> int24Data{ 0x60, 0x97, 0xF9 }; 

    // 42000000
    std::vector<unsigned char> uInt32Data{ 0x80, 0xDE, 0x80, 0x02 }; 

    // -42000000
    std::vector<unsigned char> int32Data{ 0x80, 0x21, 0x7F, 0xFD }; 

    // 420000000000
    std::vector<unsigned char> uInt64Data
    { 
        0x0, 0x68, 0xF3, 0xC9, 
        0x61, 0x0, 0x0, 0x0 
    }; 

    // -420000000000
    std::vector<unsigned char> int64Data
    { 
        0x00, 0x98, 0x0C, 0x36, 
        0x9E, 0xFF, 0xFF, 0xFF 
    };

    // [Big Endian Test Values]

    // 4200
    std::vector<unsigned char> uInt16DataBE{ 0x10, 0x68 }; 

    // -4200
    std::vector<unsigned char> int16DataBE{ 0xEF, 0x98 };

    // 420000
    std::vector<unsigned char> uInt24DataBE{ 0x06, 0x68, 0xA0 }; 

    // -420000
    std::vector<unsigned char> int24DataBE{ 0xF9, 0x97, 0x60 }; 

    // 42000000
    std::vector<unsigned char> uInt32DataBE{ 0x02, 0x80, 0xDE, 0x80 }; 

    // -42000000
    std::vector<unsigned char> int32DataBE{ 0xFD, 0x7F, 0x21, 0x80 }; 

    // 420000000000
    std::vector<unsigned char> uInt64DataBE
    { 
        0x0, 0x0, 0x0, 0x61, 
        0xC9, 0xF3, 0x68, 0x0,    
    }; 

    // -420000000000
    std::vector<unsigned char> int64DataBE
    { 
        0xFF, 0xFF, 0xFF, 0x9E,
        0x36, 0x0C, 0x98, 0x00
    };

    FieldTester<BinData::UInt8Field, unsigned int> uInt8Tester;
    FieldTester<BinData::Int8Field, int> int8Tester;
    FieldTester<BinData::UInt16Field, unsigned int> uInt16Tester;
    FieldTester<BinData::Int16Field, int> int16Tester;
    FieldTester<BinData::UInt24Field, unsigned long> uInt24Tester;
    FieldTester<BinData::Int24Field, long> int24Tester;
    FieldTester<BinData::UInt32Field, unsigned long> uInt32Tester;
    FieldTester<BinData::Int32Field, long> int32Tester;
    FieldTester<BinData::UInt64Field, unsigned long long> uInt64Tester;
    FieldTester<BinData::Int64Field, long long> int64Tester;
};

#endif