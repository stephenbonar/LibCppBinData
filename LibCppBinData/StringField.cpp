// StringField.cpp - Defines the StringField class.
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

#include "StringField.h"

namespace BinData
{
    std::string StringField::ToString() const 
    {
        return RawField::ToString(Format::Ascii);
    }

    std::string StringField::ToString(Format f) const
    {
        return RawField::ToString(f);
    }

    void StringField::SetData(std::string s)
    {
        s.copy(Data(), Size());
    }
}
