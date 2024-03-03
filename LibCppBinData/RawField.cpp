// RawField.cpp - Defines the RawField class.
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

#include "RawField.h"

namespace BinData
{
    const char* rawFieldFormatError{ 
        "RawField can only be formatted as Bin, Hex, or Ascii" };

    RawField::RawField(std::size_t size) : mSize{ size }
    {
        if (size < minFieldSize)
            throw InvalidField{ fieldSizeError };
        mData = std::make_unique<char[]>(size);
    }

    RawField::RawField(const RawField& f)
    {
        mData = std::make_unique<char[]>(f.Size());
        std::memcpy(mData.get(), f.mData.get(), f.Size());
        mSize = f.mSize;
    }

    RawField::RawField(RawField&& f)
    {
        mData = std::move(f.mData);
        mSize = f.mSize;
        f.mSize = 0;
    }

    RawField& RawField::operator=(const RawField& f)
    {
        mData = std::make_unique<char[]>(f.Size());
        std::memcpy(mData.get(), f.mData.get(), f.Size());
        mSize = f.mSize;
        return *this;
    }

    RawField& RawField::operator=(RawField&& f)
    {
        mData = std::move(f.mData);
        mSize = f.mSize;
        f.mSize = 0;
        return *this;
    }

    std::string RawField::ToString() const
    {
        if (mData == nullptr)
            throw InvalidField{ nullFieldError };
        return FormatHex(mData.get(), mSize);
    }

    std::string RawField::ToString(Format f) const
    {
        if (mData == nullptr)
            throw InvalidField{ nullFieldError };
        switch (f)
        {
            case Format::Ascii:
                return FormatAscii(mData.get(), mSize);
            case Format::Bin:
                return FormatBin(mData.get(), mSize);
            case Format::Hex:
                return FormatHex(mData.get(), mSize);
            case Format::Dec:
                throw InvalidFormat{ rawFieldFormatError };
            default:
                return ToString();
        }
    }

    std::ostream& operator<<(std::ostream& os, const RawField& f)
    {
        os << f.ToString();
        return os;
    }
}