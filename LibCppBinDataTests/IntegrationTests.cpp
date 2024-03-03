// IntegrationTests.cpp - Defines the IntegrationTests class and tests.
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

#include "IntegrationTests.h"

IntegrationTests::IntegrationTests()
{
    expectedData.magicNumber.SetData("SMB");
    for (int i = 0; i < expectedData.separator.Size(); i++)
        expectedData.separator.Data()[i] = 0xFF;
    expectedData.ui8.SetValue(42);
    expectedData.i8.SetValue(-42);
    expectedData.ui16.SetValue(4200);
    expectedData.i16.SetValue(-4200);
    expectedData.ui24.SetValue(420000);
    expectedData.i24.SetValue(-420000);
    expectedData.ui32.SetValue(420000000);
    expectedData.i32.SetValue(-420000000);
    expectedData.ui64.SetValue(420000000000);
    expectedData.i64.SetValue(-420000000000);
    expectedData.i32BE.SetValue(1776);

    expectedAppend1.ui8.SetValue(99);
    expectedAppend1.i8.SetValue(-99);
    expectedAppend1.ui16.SetValue(9999);

    expectedAppend2.ui8.SetValue(88);
    expectedAppend2.i8.SetValue(-88);
    expectedAppend2.ui16.SetValue(8888);
}

void IntegrationTests::ExpectFileDataEQ(const FileData& f1, const FileData& f2)
{
    EXPECT_EQ(f1.magicNumber.ToString(), f2.magicNumber.ToString());
    EXPECT_EQ(f1.separator.ToString(), f2.separator.ToString());
    EXPECT_EQ(f1.ui8.Value(), f2.ui8.Value());
    EXPECT_EQ(f1.i8.Value(), f2.i8.Value());
    EXPECT_EQ(f1.ui16.Value(), f2.ui16.Value());
    EXPECT_EQ(f1.i16.Value(), f2.i16.Value());
    EXPECT_EQ(f1.ui24.Value(), f2.ui24.Value());
    EXPECT_EQ(f1.i24.Value(), f2.i24.Value());
    EXPECT_EQ(f1.ui32.Value(), f2.ui32.Value());
    EXPECT_EQ(f1.i32.Value(), f2.i32.Value());
    EXPECT_EQ(f1.ui64.Value(), f2.ui64.Value());
    EXPECT_EQ(f1.i64.Value(), f2.i64.Value());
    EXPECT_EQ(f1.i32BE.Value(), f2.i32BE.Value());
}

void IntegrationTests::ExpectAppendedDataEQ(const AppendedData& d1,
    const AppendedData& d2)
{
    EXPECT_EQ(d1.ui8.Value(), d2.ui8.Value());
    EXPECT_EQ(d1.i8.Value(), d2.i8.Value());
    EXPECT_EQ(d1.ui16.Value(), d2.ui16.Value());
}

void IntegrationTests::ExpectAfterOpenState(const BinData::File& f, 
    BinData::FileMode m)
{
    ASSERT_TRUE(f.IsOpen());
    ASSERT_EQ(f.Offset(), 0);
    ASSERT_EQ(f.Mode(), m);
}

void IntegrationTests::ExpectEndOfFile(const BinData::File& f)
{
    EXPECT_EQ(f.Offset(), 47);
    EXPECT_EQ(f.IsOpen(), false);
    EXPECT_EQ(f.Size(), 47);
}

void IntegrationTests::ExpectAppendedEndOfFile(const BinData::File& f)
{
    EXPECT_EQ(f.Offset(), 51);
    EXPECT_EQ(f.Size(), 51);
}

void IntegrationTests::ReadFileData(BinData::File& f, FileData& d)
{
    ASSERT_NO_THROW(f.Read(&d.magicNumber));
    ASSERT_NO_THROW(f.Read(&d.separator));
    ASSERT_NO_THROW(f.Read(&d.ui8));
    ASSERT_NO_THROW(f.Read(&d.i8));
    ASSERT_NO_THROW(f.Read(&d.ui16));
    ASSERT_NO_THROW(f.Read(&d.i16));
    ASSERT_NO_THROW(f.Read(&d.ui24));
    ASSERT_NO_THROW(f.Read(&d.i24));
    ASSERT_NO_THROW(f.Read(&d.ui32));
    ASSERT_NO_THROW(f.Read(&d.i32));
    ASSERT_NO_THROW(f.Read(&d.ui64));
    ASSERT_NO_THROW(f.Read(&d.i64));
    ASSERT_NO_THROW(f.Read(&d.i32BE));
}

void IntegrationTests::WriteFileData(BinData::File& f, FileData& d)
{
    ASSERT_NO_THROW(f.Write(&d.magicNumber));
    ASSERT_NO_THROW(f.Write(&d.separator));
    ASSERT_NO_THROW(f.Write(&d.ui8));
    ASSERT_NO_THROW(f.Write(&d.i8));
    ASSERT_NO_THROW(f.Write(&d.ui16));
    ASSERT_NO_THROW(f.Write(&d.i16));
    ASSERT_NO_THROW(f.Write(&d.ui24));
    ASSERT_NO_THROW(f.Write(&d.i24));
    ASSERT_NO_THROW(f.Write(&d.ui32));
    ASSERT_NO_THROW(f.Write(&d.i32));
    ASSERT_NO_THROW(f.Write(&d.ui64));
    ASSERT_NO_THROW(f.Write(&d.i64));
    ASSERT_NO_THROW(f.Write(&d.i32BE));
}

void IntegrationTests::ReadAppendedData(BinData::File& f, AppendedData& d)
{
    f.Read(&d.ui8);
    f.Read(&d.i8);
    f.Read(&d.ui16);
}

void IntegrationTests::WriteAppendedData(BinData::File& f, AppendedData& d)
{
    f.Write(&d.ui8);
    f.Write(&d.i8);
    f.Write(&d.ui16);
}

void IntegrationTests::RefreshWriteDataFile()
{
    // Remove the TestWriteData file if it exists from any previous test runs
    // so we're starting with a fresh file.
    if (std::filesystem::exists("TestWriteData"))
        std::filesystem::remove("TestWriteData");
}

TEST_F(IntegrationTests, CreatesFileInstanceProperly)
{
    ASSERT_NO_THROW(BinData::CreateFile("Test.txt"));
    auto f = BinData::CreateFile("Test.txt");
    EXPECT_EQ(f.Name(), "Test.txt");
    EXPECT_EQ(f.Mode(), BinData::FileMode::Read);
    EXPECT_EQ(f.Offset(), 0);
    EXPECT_EQ(f.IsOpen(), false);
}

TEST_F(IntegrationTests, ReadsFileProperly)
{
    ASSERT_NO_THROW(BinData::CreateFile("TestReadData"));
    auto f = BinData::CreateFile("TestReadData");
    FileData data;
    ASSERT_NO_THROW(f.Open());
    ExpectAfterOpenState(f, BinData::FileMode::Read);
    ReadFileData(f, data);
    ExpectFileDataEQ(data, expectedData);
    ASSERT_NO_THROW(f.Close());
    ExpectEndOfFile(f);
}

TEST_F(IntegrationTests, WritesFileProperly)
{
    RefreshWriteDataFile();

    // Write the expected FileData to the file so we can read it back in and
    // verify it was written properly.
    ASSERT_NO_THROW(BinData::CreateFile("TestWriteData"));
    auto f = BinData::CreateFile("TestWriteData");
    ASSERT_NO_THROW(f.Open(BinData::FileMode::Write));
    ExpectAfterOpenState(f, BinData::FileMode::Write);
    WriteFileData(f, expectedData);
    ASSERT_NO_THROW(f.Close());
    ExpectEndOfFile(f);

    // Read the newly written file and compare the read data to the expected
    // data to ensure the file was written properly.
    FileData readData;
    ASSERT_NO_THROW(f.SetOffset(0));
    ASSERT_NO_THROW(f.Open(BinData::FileMode::Read));
    ReadFileData(f, readData);
    ExpectFileDataEQ(readData, expectedData);
    ASSERT_NO_THROW(f.Close());
    ExpectEndOfFile(f);

    // Append several duplicate fields to the end of the file to test the
    // WriteAppend mode.
    ASSERT_NO_THROW(f.Open(BinData::FileMode::WriteAppend));
    WriteAppendedData(f, expectedAppend1);
    EXPECT_EQ(f.Offset(), 51);
    EXPECT_EQ(f.Size(), 51);
    ASSERT_NO_THROW(f.Close());

    // Read the entire file back in as well as the appended duplicates to
    // ensure the fields were truly appended without altering the integrity
    // of the rest of the file.
    f.SetOffset(0);
    ASSERT_NO_THROW(f.Open(BinData::FileMode::ReadWrite));
    FileData readData2;
    AppendedData readAppend1;
    ReadFileData(f, readData2);
    ExpectFileDataEQ(readData2, expectedData);
    ReadAppendedData(f, readAppend1);
    ExpectAppendedDataEQ(readAppend1, expectedAppend1);
    ExpectAppendedEndOfFile(f);
    
    // Since we opened in ReadWrite mode, test that we can also change the
    // newly appended values at the end and read them back in.
    f.SetOffset(47);
    WriteAppendedData(f, expectedAppend2);
    f.SetOffset(47);
    AppendedData readAppend2;
    ReadAppendedData(f, readAppend2);
    ExpectAppendedDataEQ(readAppend2, expectedAppend2);
    ExpectAppendedEndOfFile(f);
    ASSERT_NO_THROW(f.Close());
}

TEST_F(IntegrationTests, CanReadFromSpecificOffsets)
{
    ASSERT_NO_THROW(BinData::CreateFile("TestReadData"));
    auto f = BinData::CreateFile("TestReadData");
    BinData::UInt8Field ui8;
    BinData::UInt24Field ui24;
    BinData::UInt64Field ui64;
    f.Open();
    f.SetOffset(7);
    f.Read(&ui8);
    f.SetOffset(13);
    f.Read(&ui24);
    f.SetOffset(27);
    f.Read(&ui64);
    EXPECT_EQ(ui8.Value(), expectedData.ui8.Value());
    EXPECT_EQ(ui24.Value(), expectedData.ui24.Value());
    EXPECT_EQ(ui64.Value(), expectedData.ui64.Value());
}

TEST_F(IntegrationTests, CanWriteToSpecificOffsets)
{
    RefreshWriteDataFile();
    std::filesystem::copy_file("TestReadData", "TestWriteData");
    ASSERT_NO_THROW(BinData::CreateFile("TestWriteData"));
    auto f = BinData::CreateFile("TestWriteData");
    BinData::UInt8Field ui8Write{ 99 };
    BinData::UInt24Field ui24Write{ 99 };
    BinData::UInt64Field ui64Write{ 99 };
    BinData::UInt8Field ui8Read;
    BinData::UInt24Field ui24Read;
    BinData::UInt64Field ui64Read;
    f.Open(BinData::FileMode::ReadWrite);
    f.SetOffset(7);
    f.Write(&ui8Write);
    f.SetOffset(13);
    f.Write(&ui24Write);
    f.SetOffset(27);
    f.Write(&ui64Write);
    f.SetOffset(7);
    f.Read(&ui8Read);
    f.SetOffset(13);
    f.Read(&ui24Read);
    f.SetOffset(27);
    f.Read(&ui64Read);
    EXPECT_EQ(ui8Read.Value(), 99);
    EXPECT_EQ(ui24Read.Value(), 99);
    EXPECT_EQ(ui64Read.Value(), 99);
}

TEST_F(IntegrationTests, DoesNotAllowAFileToBeOpenTwice)
{
    ASSERT_NO_THROW(BinData::CreateFile("TestReadData"));
    auto f = BinData::CreateFile("TestReadData");
    ASSERT_NO_THROW(f.Open());
    EXPECT_THROW(f.Open(), BinData::InvalidFileOperation);
    EXPECT_THROW(f.Open(BinData::FileMode::Write), 
        BinData::InvalidFileOperation);
}

TEST_F(IntegrationTests, DoesNotAllowOffsetBeyondEndOfFile)
{
    ASSERT_NO_THROW(BinData::CreateFile("TestReadData"));
    auto f = BinData::CreateFile("TestReadData");
    ASSERT_NO_THROW(f.SetOffset(47));
    EXPECT_THROW(f.SetOffset(48), BinData::InvalidFileOperation);
    EXPECT_THROW(f.SetOffset(100), BinData::InvalidFileOperation);
}

TEST_F(IntegrationTests, EnsuresFileIsOpenBeforeReadingOrWriting)
{
    RefreshWriteDataFile();
    std::filesystem::copy_file("TestReadData", "TestWriteData");
    ASSERT_NO_THROW(BinData::CreateFile("TestWriteData"));
    auto f = BinData::CreateFile("TestWriteData");
    FileData readData;
    EXPECT_THROW(f.Read(&readData.ui8), BinData::InvalidFileOperation);
    EXPECT_THROW(f.Write(&expectedData.ui8), BinData::InvalidFileOperation);
}