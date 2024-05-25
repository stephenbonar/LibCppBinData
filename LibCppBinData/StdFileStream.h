// StandardFileStream.h - Declares the StandardFileStream class.
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

#ifndef STD_FILE_STREAM_H
#define STD_FILE_STREAM_H

#include <fstream>
#include <memory>
#include "RawFile.h"
#include "FileStream.h"

namespace BinData
{
    class StdFileStream : public FileStream
    {
    public:
        StdFileStream(std::string fileName) 
            : mFileName{ fileName }, mStream{}, 
            mMode{ FileMode::Read }, mSize{ 0 }, mOffset{ 0 }
        {

        }

        std::string FileName() const override
        {
            return mFileName;
        }

        bool IsOpen() const override
        {
            return mStream.is_open();
        }

        bool Exists() const override
        {
            return std::filesystem::exists(mFileName);
        }

        std::size_t Offset() const override
        {
            return mOffset;
        }

        FileMode Mode() const override
        {
            return mMode;
        }

        std::size_t Size() const override;

        void Open(FileMode m = FileMode::Read) override;

        void Close() override
        {
            mStream.close();
        }

        void Read(Field* f) override;

        void Write(Field* f) override;

        void SetOffset(std::size_t o) override;
    private:
        std::string mFileName;
        std::fstream mStream;
        FileMode mMode;
        std::size_t mSize;
        std::size_t mOffset;
    };

    //RawFile CreateFile(std::string fileName);
}

#endif