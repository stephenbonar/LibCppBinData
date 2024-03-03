// MockField.cpp - Declares the MockField class.
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

#ifndef MOCK_FIELD_H
#define MOCK_FIELD_H

#include <gmock/gmock.h>
#include "Field.h"

class MockField : public BinData::Field
{
public:
    MOCK_METHOD(char*, Data, (), (override));
    MOCK_METHOD(std::size_t, Size, (), (const, override)); 
    MOCK_METHOD(std::string, ToString, (), (const, override));
    MOCK_METHOD(std::string, ToString, (BinData::Format f), (const, override));
};

#endif