// StandardFileStream.cpp - Defines the StandardFileStream class.
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

#include "StandardFileStream.h"

namespace BinData
{
    std::size_t StandardFileStream::Size() const
    {
        if (IsOpen())
            return mSize;
        else if (std::filesystem::exists(mFileName))
            return std::filesystem::file_size(mFileName);
        else
            return 0;
    }

    void StandardFileStream::Open(FileMode m)
    {
        if (std::filesystem::exists(mFileName))
            mSize = std::filesystem::file_size(mFileName);
        switch (m)
        {
        case FileMode::Read:
            mStream.open(mFileName, std::ios::in | std::ios::binary);
            mStream.seekg(mOffset);
            break;
        case FileMode::Write:
            mStream.open(mFileName, std::ios::out | std::ios::binary);
            mStream.seekg(mOffset);
            break;
        case FileMode::WriteAppend:
            mStream.open(mFileName, std::ios::app | std::ios::binary);
            mOffset = mSize;
            break;
        case FileMode::ReadWrite:
            mStream.open(mFileName, 
                std::ios::in | std::ios::out | std::ios::binary);
            mStream.seekg(mOffset);
            break;
        default:
            throw std::runtime_error{ "An invalid FileMode was specified" };
        }
        mMode = m;
    }

    void StandardFileStream::Read(Field* f)
    {
        mStream.read(f->Data(), f->Size());
        mOffset += f->Size();
    }

    void StandardFileStream::Write(Field* f)
    {
        mStream.write(f->Data(), f->Size());
        mOffset += f->Size();
        if (mOffset > mSize)
            mSize = mOffset;
    }

    void StandardFileStream::SetOffset(std::size_t o)
    {
        mOffset = o;
        mStream.seekg(mOffset);
    }

    RawFile CreateFile(std::string fileName)
    {
        auto standardStream = std::make_shared<StandardFileStream>(fileName);
        auto baseStream = std::static_pointer_cast<FileStream>(standardStream);
        return RawFile{ baseStream };
    }
}