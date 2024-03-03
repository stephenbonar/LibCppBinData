// FileStream.h - Declares the FileStream class.
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

#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include <cstddef>
#include <string>
#include "Field.h"

namespace BinData
{
    enum class FileMode
    {
        Read,
        Write,
        WriteAppend,
        ReadWrite
    };

    class FileStream
    {
    public:
        virtual std::string FileName() const = 0;

        virtual bool IsOpen() const = 0;

        virtual bool Exists() const = 0;

        virtual std::size_t Offset() const = 0;

        virtual FileMode Mode() const = 0;

        virtual std::size_t Size() const = 0;

        virtual void Open(FileMode mode = FileMode::Read) = 0;

        virtual void Close() = 0;

        virtual void Read(Field* f) = 0;

        virtual void Write(Field* f) = 0;

        virtual void SetOffset(std::size_t o) = 0;
    };
}

#endif