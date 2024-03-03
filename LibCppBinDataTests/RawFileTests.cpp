// RawFileTests.cpp - Defines the RawFileTests class and tests.
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

#include "RawFileTests.h"

using ::testing::Exactly;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

RawFileTests::RawFileTests()
{
    mockStream = std::make_shared<MockFileStream>();
    mockStreamBasePtr = std::static_pointer_cast<BinData::FileStream>(
        mockStream);
}

void RawFileTests::InitializeTestFile()
{
    ASSERT_NO_THROW(testFile = 
        std::make_unique<BinData::RawFile>(mockStreamBasePtr));
}

void RawFileTests::ExpectClosed(BinData::FileMode m)
{
    EXPECT_EQ(testFile->IsOpen(), false);
    EXPECT_EQ(testFile->Mode(), m);
}

void RawFileTests::ExpectOpened(BinData::FileMode m)
{
    EXPECT_EQ(testFile->IsOpen(), true);
    EXPECT_EQ(testFile->Mode(), m);
}

void RawFileTests::ExpectOpensAndClosesProperly(BinData::FileMode m)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(*mockStream, Mode())
        .WillOnce(Return(BinData::FileMode::Read))
        .WillOnce(Return(m))
        .WillOnce(Return(m));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(m))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Close())
        .Times(Exactly(1));

    ExpectClosed(BinData::FileMode::Read);
    ASSERT_NO_THROW(testFile->Open(m));
    ExpectOpened(m);
    testFile->Close();
    ExpectClosed(m);
}

TEST_F(RawFileTests, CreatesFileProperly)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, FileName())
        .WillOnce(Return("Test"));
    EXPECT_CALL(*mockStream, IsOpen())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockStream, Size())
        .Times(Exactly(1))
        .WillRepeatedly(Return(100));
    EXPECT_CALL(*mockStream, Mode())
        .Times(Exactly(1))
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Offset())
        .Times(Exactly(1))
        .WillRepeatedly(Return(0));

    EXPECT_EQ(testFile->Name(), "Test");
    EXPECT_EQ(testFile->IsOpen(), false);
    EXPECT_EQ(testFile->Mode(), BinData::FileMode::Read);
    EXPECT_EQ(testFile->Size(), 100);
    EXPECT_EQ(testFile->Offset(), 0);
}

TEST_F(RawFileTests, DoesNotCreateInvalidFile)
{
    ASSERT_THROW(BinData::RawFile f(nullptr), BinData::InvalidFile);
}

TEST_F(RawFileTests, DoesNotAttemptToOpenNonExistantFileForReading)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false));
    EXPECT_CALL(*mockStream, Exists())
        .WillOnce(Return(false));
    EXPECT_CALL(*mockStream, Open(_))
        .Times(Exactly(0));

    EXPECT_THROW(testFile->Open(BinData::FileMode::Read), 
        BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, FileCannotBeOpenTwice)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen)
        .Times(Exactly(3))
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Read))
        .Times(Exactly(1));

    testFile->Open(BinData::FileMode::Read);
    EXPECT_THROW(testFile->Open(BinData::FileMode::Read), 
        BinData::InvalidFileOperation);
    EXPECT_THROW(testFile->Open(BinData::FileMode::Write), 
        BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, OpensAndClosesFileForReadingProperly)
{
    ExpectOpensAndClosesProperly(BinData::FileMode::Read);
}

TEST_F(RawFileTests, OpensAndClosesFileForWritingProperly)
{
    ExpectOpensAndClosesProperly(BinData::FileMode::Write);
}

TEST_F(RawFileTests, OpensAndClosesFileForAppendingProperly)
{
    ExpectOpensAndClosesProperly(BinData::FileMode::WriteAppend);
}

TEST_F(RawFileTests, OpensAndClosesFileForReadWriteProperly)
{
    ExpectOpensAndClosesProperly(BinData::FileMode::ReadWrite);
}

TEST_F(RawFileTests, ReadsFileProperly)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Read))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Mode())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Size())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(4));
    EXPECT_CALL(mockField, Size())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(4));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(0));
    EXPECT_CALL(*mockStream, Read(&mockField))
        .Times(Exactly(1));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Read));
    ASSERT_NO_THROW(testFile->Read(&mockField));
}

TEST_F(RawFileTests, WritesFileProperly)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Write))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Mode())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(BinData::FileMode::Write));
    EXPECT_CALL(*mockStream, Size())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(4));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(0));
    EXPECT_CALL(*mockStream, Write(&mockField))
        .Times(Exactly(1));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Write));
    ASSERT_NO_THROW(testFile->Write(&mockField));
}

TEST_F(RawFileTests, AppendsFileProperly)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::WriteAppend))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Mode())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(BinData::FileMode::WriteAppend));
    EXPECT_CALL(*mockStream, Size())
        .WillOnce(Return(4))
        .WillOnce(Return(8));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(4))
        .WillOnce(Return(8));
    EXPECT_CALL(*mockStream, Write(&mockField))
        .Times(Exactly(1));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::WriteAppend));
    ASSERT_NO_THROW(testFile->Write(&mockField));
    EXPECT_EQ(testFile->Offset(), 8);
    EXPECT_EQ(testFile->Size(), 8);
}

TEST_F(RawFileTests, ReadsWritesFileProperly)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::ReadWrite))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Mode())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(BinData::FileMode::ReadWrite));
    EXPECT_CALL(*mockStream, Size())
        .WillOnce(Return(4))
        .WillRepeatedly(Return(8));
    EXPECT_CALL(mockField, Size())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(4));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(0))
        .WillOnce(Return(4))
        .WillRepeatedly(Return(8));
    EXPECT_CALL(*mockStream, Read(&mockField))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Write(&mockField))
        .Times(Exactly(1));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::ReadWrite));
    ASSERT_NO_THROW(testFile->Read(&mockField));
    ASSERT_NO_THROW(testFile->Write(&mockField));
    EXPECT_EQ(testFile->Offset(), 8);
    EXPECT_EQ(testFile->Size(), 8);
}

TEST_F(RawFileTests, DoesNotAttemptToReadUnopenedFile)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Read(_))
        .Times(Exactly(0));

    EXPECT_THROW(testFile->Read(&mockField), BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, DoesNotAttemptToWriteUnopenedFile)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .Times(Exactly(1))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Write));
    EXPECT_CALL(*mockStream, Write(_))
        .Times(Exactly(0));

    EXPECT_THROW(testFile->Write(&mockField), BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, DoesNotAttemptToReadFileOpenedForWriting)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Write))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Write));
    EXPECT_CALL(*mockStream, Read(_))
        .Times(Exactly(0));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Write));
    EXPECT_THROW(testFile->Read(&mockField), BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, DoesNotAttemptToWriteFileOpenedForReading)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Read))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Write(_))
        .Times(Exactly(0));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Read));
    EXPECT_THROW(testFile->Write(&mockField), BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, DoesNotReadBeyondEndOfFile)
{
    InitializeTestFile();
    
    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Size())
        .WillRepeatedly(Return(24));
    EXPECT_CALL(mockField, Size())
        .WillRepeatedly(Return(4));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(24));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Read))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, SetOffset(24))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Read(_))
        .Times(Exactly(0));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Read));
    ASSERT_NO_THROW(testFile->SetOffset(24));
    EXPECT_THROW(testFile->Read(&mockField), BinData::InvalidFileOperation);
}

TEST_F(RawFileTests, ReadingAdvancesTheFileOffset)
{
    InitializeTestFile();
    
    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(mockField, Size())
        .WillRepeatedly(Return(4));
    EXPECT_CALL(*mockStream, Size())
        .Times(AtLeast(3))
        .WillRepeatedly(Return(12));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Read));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Read))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(4))
        .WillOnce(Return(4))
        .WillOnce(Return(8))
        .WillOnce(Return(8))
        .WillOnce(Return(12));
    EXPECT_CALL(*mockStream, Read(_))
        .Times(Exactly(3));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Read));
    EXPECT_EQ(testFile->Offset(), 0);
    ASSERT_NO_THROW(testFile->Read(&mockField));
    EXPECT_EQ(testFile->Offset(), 4);
    ASSERT_NO_THROW(testFile->Read(&mockField));
    EXPECT_EQ(testFile->Offset(), 8);
    ASSERT_NO_THROW(testFile->Read(&mockField));
    EXPECT_EQ(testFile->Offset(), 12);
}

TEST_F(RawFileTests, WritingAdvancesTheFileOffset)
{
    InitializeTestFile();
    
    EXPECT_CALL(*mockStream, IsOpen())
        .WillOnce(Return(false))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Exists)
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockStream, Open(BinData::FileMode::Write))
        .Times(Exactly(1));
    EXPECT_CALL(*mockStream, Size())
        .WillOnce(Return(0))
        .WillOnce(Return(4))
        .WillOnce(Return(8));
    EXPECT_CALL(*mockStream, Offset())
        .WillOnce(Return(0))
        .WillOnce(Return(0))
        .WillOnce(Return(4))
        .WillOnce(Return(4))
        .WillOnce(Return(8))
        .WillOnce(Return(8))
        .WillOnce(Return(12));
    EXPECT_CALL(*mockStream, Mode())
        .WillRepeatedly(Return(BinData::FileMode::Write));
    EXPECT_CALL(*mockStream, Write(_))
        .Times(Exactly(3));

    ASSERT_NO_THROW(testFile->Open(BinData::FileMode::Write));
    EXPECT_EQ(testFile->Offset(), 0);
    ASSERT_NO_THROW(testFile->Write(&mockField));
    EXPECT_EQ(testFile->Offset(), 4);
    ASSERT_NO_THROW(testFile->Write(&mockField));
    EXPECT_EQ(testFile->Offset(), 8);
    ASSERT_NO_THROW(testFile->Write(&mockField));
    EXPECT_EQ(testFile->Offset(), 12);
}

TEST_F(RawFileTests, DoesNotAllowSettingOffsetBeyondFileSize)
{
    InitializeTestFile();

    EXPECT_CALL(*mockStream, Size())
        .Times(1)
        .WillRepeatedly(Return(12));
    
    EXPECT_THROW(testFile->SetOffset(13), BinData::InvalidFileOperation);
}