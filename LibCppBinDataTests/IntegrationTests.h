// IntegrationTests.h - Declares the IntegrationTests class.
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

#ifndef INTEGRATION_TESTS_H
#define INTEGRATION_TESTS_H

#include <filesystem>
#include <gtest/gtest.h>
#include "File.h"
#include "StringField.h"
#include "RawField.h"
#include "IntField.h"
#include "StdFileStream.h"

struct FileData
{
    BinData::StringField magicNumber{ 3 };
    BinData::RawField separator{ 4 };
    BinData::UInt8Field ui8;
    BinData::Int8Field i8;
    BinData::UInt16Field ui16;
    BinData::Int16Field i16;
    BinData::UInt24Field ui24;
    BinData::Int24Field i24;
    BinData::UInt32Field ui32;
    BinData::Int32Field i32;
    BinData::UInt64Field ui64;
    BinData::Int64Field i64;
    BinData::Int32Field i32BE{ BinData::FieldEndianness::Big };
};

struct AppendedData
{
    BinData::UInt8Field ui8;
    BinData::Int8Field i8;
    BinData::UInt16Field ui16;
};

class IntegrationTests : public ::testing::Test
{
protected:
    FileData expectedData;
    AppendedData expectedAppend1;
    AppendedData expectedAppend2;

    IntegrationTests();

    void ExpectFileDataEQ(const FileData& f1, const FileData& f2);

    void ExpectAppendedDataEQ(const AppendedData& d1, const AppendedData& d2);

    void ExpectAfterOpenState(const BinData::File& f, BinData::FileMode m);

    void ExpectEndOfFile(const BinData::File& f);

    void ExpectAppendedEndOfFile(const BinData::File& f);

    void ReadFileData(BinData::File& f, FileData& d);

    void WriteFileData(BinData::File& f, FileData& d);

    void ReadAppendedData(BinData::File& f, AppendedData& d);

    void WriteAppendedData(BinData::File& f, AppendedData& d);

    void RefreshWriteDataFile();
};

#endif