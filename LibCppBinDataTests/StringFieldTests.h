// StringFieldTests.h - Declares the StringFieldTests class.
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

#ifndef STRING_FIELD_TESTS_H
#define STRING_FIELD_TESTS_H

#include <cstring>
#include <vector>
#include <memory>
#include <gtest/gtest.h>
#include "Format.h"
#include "StringField.h"

const char* nonPrintableString{ "...." };
const char* printableString{ "This is a test!" };
const char* printableStringSmaller{ "This " };
const char* printableStringLarger{ "This is a test!....." };
const char* mixedString{ "T.E.S.T" };
const char* mixedStringHex{ "54 01 45 7F 53 80 54" };
const char* mixedStringBin
{ 
    "01010100 00000001 01000101 01111111 01010011 10000000 01010100"
};

class StringFieldTests : public ::testing::Test
{
protected:
    StringFieldTests();

    void ExpectCreatedProperly(std::size_t size);

    std::unique_ptr<BinData::StringField> nonPrintableField;
    std::unique_ptr<BinData::StringField> printableField;
    std::unique_ptr<BinData::StringField> mixedField;
};

#endif