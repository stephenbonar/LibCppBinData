// MockFileStream.h - Declares the MockFileStream class.
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

#ifndef MOCK_FILE_STREAM_H
#define MOCK_FILE_STREAM_H

#include <gmock/gmock.h>
#include "FileStream.h"
#include "Field.h"

class MockFileStream : public BinData::FileStream
{
public:
    MOCK_METHOD(std::string, FileName, (), (const, override));
    MOCK_METHOD(bool, IsOpen, (), (const, override));
    MOCK_METHOD(bool, Exists, (), (const, override));
    MOCK_METHOD(std::size_t, Offset, (), (const, override));
    MOCK_METHOD(BinData::FileMode, Mode, (), (const, override));
    MOCK_METHOD(std::size_t, Size, (), (const, override));
    MOCK_METHOD(void, Open, (BinData::FileMode mode), (override));
    MOCK_METHOD(void, Close, (), (override));
    MOCK_METHOD(void, Read, (BinData::Field* f), (override));
    MOCK_METHOD(void, Write, (BinData::Field* f), (override));
    MOCK_METHOD(void, SetOffset, (std::size_t o), (override));
};

#endif