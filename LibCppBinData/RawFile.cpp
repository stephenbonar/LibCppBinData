// RawFile.cpp - Defines the RawFile class.
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

#include "RawFile.h"

namespace BinData
{
    RawFile::RawFile(std::shared_ptr<FileStream> stream) 
        : mStream{ stream }
    {
        if (mStream == nullptr)
            throw InvalidFile{ "file stream cannot be null" };
    }

    void RawFile::Open(FileMode m)
    {
        if (IsOpen())
            throw InvalidFileOperation{ "File is already open" };
        if (!Exists() && m == FileMode::Read)
            throw InvalidFileOperation{ "File does not exist" };
        mStream->Open(m);
    }

    void RawFile::Read(Field* f)
    {
        if (!IsOpenForReading())
            throw InvalidFileOperation{ "File is not open for reading" };
        if (mStream->Offset() + f->Size() > mStream->Size())
            throw InvalidFileOperation{ "Cannot read beyond end of file" };
        mStream->Read(f);
    }

    void RawFile::Write(Field* f)
    {
        if (!IsOpenForWriting())
            throw InvalidFileOperation{ "File is not open for writing" };
        if (mStream->Offset() > mStream->Size())
        {
            throw InvalidFileOperation
            { 
                "Offset must not be beyond end of file" 
            };
        }
        mStream->Write(f);
    }

    void RawFile::SetOffset(std::size_t o)
    {
        if (o > Size())
            throw InvalidFileOperation{ "Offset cannot be beyond file size" };
        //mOffset = offset;
        mStream->SetOffset(o);
    }

    bool RawFile::IsOpenForReading()
    {
        bool correctMode = mStream->Mode() == FileMode::Read;
        correctMode = correctMode || mStream->Mode() == FileMode::ReadWrite;
        return correctMode && IsOpen();
    }

    bool RawFile::IsOpenForWriting()
    {
        bool correctMode = mStream->Mode() == FileMode::Write;
        correctMode = correctMode || mStream->Mode() == FileMode::WriteAppend;
        correctMode = correctMode || mStream->Mode() == FileMode::ReadWrite;
        return correctMode && IsOpen();
    }

    std::size_t RawFile::Size() const
    {
        return mStream->Size();
    }
}