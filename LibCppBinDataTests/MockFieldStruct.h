// MockFieldStruct.h - Declares the MockFieldStruct class.
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
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MOCK_FIELD_STRUCT_H
#define MOCK_FIELD_STRUCT_H

#include <vector>
#include <memory>
#include <gmock/gmock.h>
#include "FieldStruct.h"
#include "Field.h"

namespace BinData
{
    class MockFieldStruct : public BinData::FieldStruct
    {
    public:
        MOCK_METHOD(std::vector<std::shared_ptr<Field>>, Fields, (), (const, override));

        /*
        MOCK_METHOD(char*, Data, (), (override));
        MOCK_METHOD(std::size_t, Size, (), (const, override)); 
        MOCK_METHOD(std::string, ToString, (), (const, override));
        MOCK_METHOD(std::string, ToString, (BinData::Format f), (const, override));
        */
    };
}

#endif