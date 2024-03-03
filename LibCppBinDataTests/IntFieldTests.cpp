// IntFieldTests.cpp - Defines the IntFieldTests class and tests.
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

#include "IntFieldTests.h"

TEST_F(IntFieldTests, CreatesIntFieldsProperly)
{
    uInt8Tester.ExpectCreatedProperly(1);
    uInt16Tester.ExpectCreatedProperly(2);
    uInt24Tester.ExpectCreatedProperly(3);
    uInt32Tester.ExpectCreatedProperly(4);
    uInt64Tester.ExpectCreatedProperly(8);

    int8Tester.ExpectCreatedProperly(1);
    int16Tester.ExpectCreatedProperly(2);
    int24Tester.ExpectCreatedProperly(3);
    int32Tester.ExpectCreatedProperly(4);
    int64Tester.ExpectCreatedProperly(8);
}

TEST_F(IntFieldTests, CreatesIntFieldsWithAlternateConstructorsProperly)
{
    BinData::Int16Field f16{ int16Val };
    EXPECT_EQ(f16.Value(), int16Val);

    BinData::Int16Field f16BE{ int16Val, BinData::FieldEndianness::Big };
    for (int i = 0; i < f16BE.Size(); i++)
        EXPECT_EQ(f16BE.Data()[i], static_cast<char>(int16DataBE[i]));
}

TEST_F(IntFieldTests, ConvertsToStringProperly)
{
    uInt8Tester.ExpectProperString(uInt8Data, uInt8Dec);
    uInt16Tester.ExpectProperString(uInt16Data, uInt16Dec);
    uInt24Tester.ExpectProperString(uInt24Data, uInt24Dec);
    uInt32Tester.ExpectProperString(uInt32Data, uInt32Dec);
    uInt64Tester.ExpectProperString(uInt64Data, uInt64Dec);

    int8Tester.ExpectProperString(int8Data, int8Dec);
    int16Tester.ExpectProperString(int16Data, int16Dec);
    int24Tester.ExpectProperString(int24Data, int24Dec);
    int32Tester.ExpectProperString(int32Data, int32Dec);
    int64Tester.ExpectProperString(int64Data, int64Dec);
}

TEST_F(IntFieldTests, ConvertsToValueProperly)
{
    // Only run these tests on little-endian systems via conditional 
    // compilation. On big endian systems, run these same tests with the
    // vectors ending in BE (except for 8-bit fields, which are the same on
    // either endianness).
    uInt8Tester.ExpectProperValue(uInt8Data, uInt8Val);
    uInt16Tester.ExpectProperValue(uInt16Data, uInt16Val);
    uInt24Tester.ExpectProperValue(uInt24Data, uInt24Val);
    uInt32Tester.ExpectProperValue(uInt32Data, uInt32Val);
    uInt64Tester.ExpectProperValue(uInt64Data, uInt64Val);

    int8Tester.ExpectProperValue(int8Data, int8Val);
    int16Tester.ExpectProperValue(int16Data, int16Val);
    int24Tester.ExpectProperValue(int24Data, int24Val);
    int32Tester.ExpectProperValue(int32Data, int32Val);
    int64Tester.ExpectProperValue(int64Data, int64Val);

    // TODO: Add conditional compiliation that enables these tests and
    // disables the little endian ones on big-endian systems.
}

TEST_F(IntFieldTests, ConvertsToValueProperlyBigEndian)
{
    // Only run these tests on little-endian systems via conditional 
    // compilation. On big endian systems, run these same tests with th
    // vectors that DO NOT end in BE (except for 8-bit fields, which are the 
    // same on either endianness).
    uInt8Tester.ExpectProperValueBE(uInt8Data, uInt8Val);
    uInt16Tester.ExpectProperValueBE(uInt16DataBE, uInt16Val);
    uInt24Tester.ExpectProperValueBE(uInt24DataBE, uInt24Val);
    uInt32Tester.ExpectProperValueBE(uInt32DataBE, uInt32Val);
    uInt64Tester.ExpectProperValueBE(uInt64DataBE, uInt64Val);
    
    int8Tester.ExpectProperValueBE(int8Data, int8Val);
    int16Tester.ExpectProperValueBE(int16DataBE, int16Val);
    int24Tester.ExpectProperValueBE(int24DataBE, int24Val);
    int32Tester.ExpectProperValueBE(int32DataBE, int32Val);
    int64Tester.ExpectProperValueBE(int64DataBE, int64Val);

    // TODO: Add conditional compiliation that enables these tests and
    // disables the little endian ones on big-endian systems.
}

TEST_F(IntFieldTests, ConvertsToHexStringProperly)
{
    // Only run these tests on little-endian systems via conditional 
    // compilation. On big endian systems, run these same tests with the
    // vectors ending in BE (except for 8-bit fields, which are the same on
    // either endianness).
    BinData::Format hex = BinData::Format::Hex;

    uInt8Tester.ExpectProperString(uInt8Data, uInt8Hex, hex);
    uInt16Tester.ExpectProperString(uInt16Data, uInt16Hex, hex);
    uInt24Tester.ExpectProperString(uInt24Data, uInt24Hex, hex);
    uInt32Tester.ExpectProperString(uInt32Data, uInt32Hex, hex);
    uInt64Tester.ExpectProperString(uInt64Data, uInt64Hex, hex);

    int8Tester.ExpectProperString(int8Data, int8Hex, hex);
    int16Tester.ExpectProperString(int16Data, int16Hex, hex);
    int24Tester.ExpectProperString(int24Data, int24Hex, hex);
    int32Tester.ExpectProperString(int32Data, int32Hex, hex);
    int64Tester.ExpectProperString(int64Data, int64Hex, hex);

    // TODO: Add conditional compiliation that enables these tests and
    // disables the little endian ones on big-endian systems.
}

TEST_F(IntFieldTests, DoesNotAcceptAsciiFormat)
{
    BinData::Int16Field f{ 42 };
    EXPECT_THROW(f.ToString(BinData::Format::Ascii), BinData::InvalidFormat);
}

TEST_F(IntFieldTests, ConvertsToBinaryStringProperly)
{
    // Only run these tests on little-endian systems via conditional 
    // compilation. On big endian systems, run these same tests with the
    // vectors ending in BE (except for 8-bit fields, which are the same on
    // either endianness).
    BinData::Format bin = BinData::Format::Bin;

    uInt8Tester.ExpectProperString(uInt8Data, uInt8Bin, bin);
    uInt16Tester.ExpectProperString(uInt16Data, uInt16Bin, bin);
    uInt24Tester.ExpectProperString(uInt24Data, uInt24Bin, bin);
    uInt32Tester.ExpectProperString(uInt32Data, uInt32Bin, bin);
    uInt64Tester.ExpectProperString(uInt64Data, uInt64Bin, bin);

    int8Tester.ExpectProperString(int8Data, int8Bin, bin);
    int16Tester.ExpectProperString(int16Data, int16Bin, bin);
    int24Tester.ExpectProperString(int24Data, int24Bin, bin);
    int32Tester.ExpectProperString(int32Data, int32Bin, bin);
    int64Tester.ExpectProperString(int64Data, int64Bin, bin);

    // TODO: Add conditional compiliation that enables these tests and
    // disables the little endian ones on big-endian systems.
}

TEST_F(IntFieldTests, SetsValueProperly)
{
    uInt8Tester.ExpectValueSetProperly(uInt8Val);
    uInt16Tester.ExpectValueSetProperly(uInt16Val);
    uInt24Tester.ExpectValueSetProperly(uInt24Val);
    uInt32Tester.ExpectValueSetProperly(uInt32Val);
    uInt64Tester.ExpectValueSetProperly(uInt64Val);

    int8Tester.ExpectValueSetProperly(int8Val);
    int16Tester.ExpectValueSetProperly(int16Val);
    int24Tester.ExpectValueSetProperly(int24Val);
    int32Tester.ExpectValueSetProperly(int32Val);
    int64Tester.ExpectValueSetProperly(int64Val);
}

TEST_F(IntFieldTests, SetsValueProperlyBigEndian)
{
    uInt8Tester.ExpectValueSetProperlyBE(uInt8Data, uInt8Val);
    uInt16Tester.ExpectValueSetProperlyBE(uInt16DataBE, uInt16Val);
    uInt24Tester.ExpectValueSetProperlyBE(uInt24DataBE, uInt24Val);
    uInt32Tester.ExpectValueSetProperlyBE(uInt32DataBE, uInt32Val);
    uInt64Tester.ExpectValueSetProperlyBE(uInt64DataBE, uInt64Val);

    int8Tester.ExpectValueSetProperlyBE(int8Data, int8Val);
    int16Tester.ExpectValueSetProperlyBE(int16DataBE, int16Val);
    int24Tester.ExpectValueSetProperlyBE(int24DataBE, int24Val);
    int32Tester.ExpectValueSetProperlyBE(int32DataBE, int32Val);
    int64Tester.ExpectValueSetProperlyBE(int64DataBE, int64Val);
}

TEST_F(IntFieldTests, CreatesDeepCopies)
{
    uInt8Tester.ExpectDeepCopy();
    uInt16Tester.ExpectDeepCopy();
    uInt24Tester.ExpectDeepCopy();
    uInt32Tester.ExpectDeepCopy();
    uInt64Tester.ExpectDeepCopy();

    int8Tester.ExpectDeepCopy();
    int16Tester.ExpectDeepCopy();
    int24Tester.ExpectDeepCopy();
    int32Tester.ExpectDeepCopy();
    int64Tester.ExpectDeepCopy();
}

TEST_F(IntFieldTests, MovesFieldsProperly)
{
    uInt8Tester.ExpectMove();
    uInt16Tester.ExpectMove();
    uInt24Tester.ExpectMove();
    uInt32Tester.ExpectMove();
    uInt64Tester.ExpectMove();

    int8Tester.ExpectMove();
    int16Tester.ExpectMove();
    int24Tester.ExpectMove();
    int32Tester.ExpectMove();
    int64Tester.ExpectMove();
}

TEST_F(IntFieldTests, WritesToOutputStreamProperly)
{
    uInt8Tester.ExpectWritesToStream();
    uInt16Tester.ExpectWritesToStream();
    uInt24Tester.ExpectWritesToStream();
    uInt32Tester.ExpectWritesToStream();
    uInt64Tester.ExpectWritesToStream();

    int8Tester.ExpectWritesToStream();
    int16Tester.ExpectWritesToStream();
    int24Tester.ExpectWritesToStream();
    int32Tester.ExpectWritesToStream();
    int64Tester.ExpectWritesToStream();
}