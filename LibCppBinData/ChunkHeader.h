// ChunkHeader.h - Declares the ChunkHeader class.
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

#ifndef BIN_DATA_CHUNK_HEADER_H
#define BIN_DATA_CHUNK_HEADER_H

#include <vector>
#include <memory>
#include "Field.h"
#include "StringField.h"
#include "IntField.h"
#include "FieldStruct.h"
#include "Endianness.h"

namespace BinData
{
    class ChunkHeader : public FieldStruct
    {
    public:
        ChunkHeader(Endianness endianness = Endianness::Little) :
            fields
            {
                std::make_shared<StringField>(4),
                std::make_shared<UInt32Field>(endianness)
            }
        { }

        std::shared_ptr<StringField> ID() 
        {
            return std::static_pointer_cast<StringField>(fields.at(0));
        }

        std::shared_ptr<UInt32Field> Size()
        {
            return std::static_pointer_cast<UInt32Field>(fields.at(1));
        }

        std::vector<std::shared_ptr<Field>> Fields() const override 
        {
            return fields; 
        }
    private:
        std::vector<std::shared_ptr<Field>> fields;
    };
}

#endif