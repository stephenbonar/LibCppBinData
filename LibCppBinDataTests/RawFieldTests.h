// RawFieldTests.h - Declares the RawFieldTests class.
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

#ifndef RAW_FIELD_TESTS_H
#define RAW_FIELD_TESTS_H

#include <cstring>
#include <cstddef>
#include <sstream>
#include <vector>
#include <memory>
#include <gtest/gtest.h>
#include "RawField.h"

const char* testAsciiString{ "Test!" };
const char* testHexString{ "54 65 73 74 21" };
const char* testBinString{ "01010100 01100101 01110011 01110100 00100001" };

class RawFieldTests : public ::testing::Test
{
protected:
    RawFieldTests();

    void ExpectCreatedProperly(std::size_t size);

    std::unique_ptr<BinData::RawField> testField;
};

#endif