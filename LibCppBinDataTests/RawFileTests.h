// RawFileTests.h - Declares the RawFileTest class.
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

#ifndef RAW_FILE_TESTS_H
#define RAW_FILE_TESTS_H

#include <string>
#include <memory>
#include <gtest/gtest.h>
#include "MockFileStream.h"
#include "RawFile.h"
#include "FileStream.h"
#include "MockField.h"
#include "MockFieldStruct.h"

namespace BinData
{
    class RawFileTests : public ::testing::Test
    {
    protected:
        std::shared_ptr<MockFileStream> mockStream;
        std::shared_ptr<BinData::FileStream> mockStreamBasePtr;
        std::unique_ptr<BinData::RawFile> testFile;
        MockField mockField;
        MockFieldStruct mockFieldStruct;

        RawFileTests();

        void InitializeTestFile();

        void ExpectClosed(BinData::FileMode m);

        void ExpectOpened(BinData::FileMode m);

        void ExpectOpensAndClosesProperly(BinData::FileMode m);
    };
}


#endif