// StringFieldTests.cpp - Defines the StringFieldTests class and tests.
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

#include "StringFieldTests.h"

StringFieldTests::StringFieldTests()
{
    std::vector<char> nonPrt{ '\x01', '\x7F', '\x80', '\xFF' };
    std::vector<char> prt{ 
        'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 
        'a', ' ', 't', 'e', 's', 't', '!' 
    };
    std::vector<char> mixed{ 'T', '\x01', 'E', '\x7F', 'S', '\x80', 'T' };

    nonPrintableField = std::make_unique<BinData::StringField>(nonPrt.size());
    printableField = std::make_unique<BinData::StringField>(prt.size());
    mixedField = std::make_unique<BinData::StringField>(mixed.size());

    std::memcpy(nonPrintableField->Data(), nonPrt.data(), nonPrt.size());
    std::memcpy(printableField->Data(), prt.data(), prt.size());
    std::memcpy(mixedField->Data(), mixed.data(), mixed.size());
}

void StringFieldTests::ExpectCreatedProperly(std::size_t size)
{
    ASSERT_NO_THROW(BinData::StringField{ size });
    BinData::StringField f{ size };
    EXPECT_EQ(f.Size(), size);
    std::stringstream expectedStringStream;
    for (std::size_t i = 0; i < size; i++)
    {
        expectedStringStream << ".";
    }
    EXPECT_EQ(f.ToString(), expectedStringStream.str());
}

TEST_F(StringFieldTests, CreatesStringFieldProperly)
{
    ExpectCreatedProperly(1);
    ExpectCreatedProperly(10);
    ExpectCreatedProperly(255);
}

TEST_F(StringFieldTests, CreatesIntFieldsWithAlternateConstructorsProperly)
{
    BinData::StringField f{ printableString, 15 };
    EXPECT_EQ(f.ToString(), printableString);
}

TEST_F(StringFieldTests, DoesNotCreateInvalidStringField)
{
    ASSERT_THROW(BinData::StringField{ 0 }, BinData::InvalidField);
}

TEST_F(StringFieldTests, ConvertsToStringProperly)
{
    EXPECT_EQ(nonPrintableField->ToString(), nonPrintableString);
    EXPECT_EQ(printableField->ToString(), printableString);
    EXPECT_EQ(mixedField->ToString(), mixedString);
}

TEST_F(StringFieldTests, ConvertsToStringWithSpecifiedFormatProperly)
{
    EXPECT_EQ(mixedField->ToString(BinData::Format::Ascii), mixedString);
    EXPECT_EQ(mixedField->ToString(BinData::Format::Hex), mixedStringHex);
    EXPECT_EQ(mixedField->ToString(BinData::Format::Bin), mixedStringBin);
}

TEST_F(StringFieldTests, DoesNotAcceptDecFormat)
{
    ASSERT_THROW(mixedField->ToString(BinData::Format::Dec), 
        BinData::InvalidFormat);
}

TEST_F(StringFieldTests, SetsValuesProperly)
{
    BinData::StringField smallerField{ 5 };
    BinData::StringField sameSizeField{ 15 };
    BinData::StringField largerField{ 20 };

    smallerField.SetData(printableString);
    sameSizeField.SetData(printableString);
    largerField.SetData(printableString);

    EXPECT_EQ(smallerField.ToString(), printableStringSmaller);
    EXPECT_EQ(sameSizeField.ToString(), printableString);
    EXPECT_EQ(largerField.ToString(), printableStringLarger);
}

TEST_F(StringFieldTests, CreatesDeepCopies)
{
    BinData::StringField f2 = BinData::StringField{ *printableField };
    EXPECT_NE(f2.Data(), printableField->Data());
    EXPECT_EQ(f2.Size(), printableField->Size());
    EXPECT_EQ(f2.ToString(), printableField->ToString());

    BinData::StringField f3{ 1 };
    f3 = f2;
    EXPECT_NE(f2.Data(), f3.Data());
    EXPECT_EQ(f2.Size(), f3.Size());
    EXPECT_EQ(f2.ToString(), f3.ToString());
}

TEST_F(StringFieldTests, MovesFieldsProperly)
{
    auto size = printableField->Size();
    BinData::StringField f2 = BinData::StringField(std::move(*printableField));
    ASSERT_THROW(printableField->ToString(), BinData::InvalidField);
    EXPECT_EQ(printableField->Data(), nullptr);
    EXPECT_EQ(printableField->Size(), 0);
    ASSERT_NE(f2.Data(), nullptr);
    EXPECT_EQ(f2.Size(), size);
    EXPECT_EQ(f2.ToString(), printableString);

    BinData::StringField f3{ 1 };
    f3 = std::move(f2);
    ASSERT_THROW(printableField->ToString(), BinData::InvalidField);
    ASSERT_THROW(f2.ToString(), BinData::InvalidField);
    EXPECT_EQ(printableField->Data(), nullptr);
    EXPECT_EQ(f2.Data(), nullptr);
    EXPECT_EQ(printableField->Size(), 0);
    EXPECT_EQ(f2.Size(), 0);
    ASSERT_NE(f3.Data(), nullptr);
    EXPECT_EQ(f3.Size(), size);
    EXPECT_EQ(f3.ToString(), printableString);
}

TEST_F(StringFieldTests, WritesToOutputStreamProperly)
{
    std::stringstream s;
    s << *printableField;
    EXPECT_EQ(s.str(), printableField->ToString());
}