// RawFile.h - Declares the RawFile class.
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

#ifndef BIN_DATA_RAW_FILE_H
#define BIN_DATA_RAW_FILE_H

#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <memory>
#include "Field.h"
#include "FileStream.h"
#include "StdFileStream.h"
#include "File.h"

namespace BinData
{
    class RawFile : public File
    {
    public:
        RawFile(std::string fileName);

        /// @brief Constructs a new instance of File.
        /// @param stream The FileStream to use for reading and writing. 
        /// @invariant A file can only be open in one mode at a time.
        /// @invariant stream should not be null
        RawFile(std::shared_ptr<FileStream> stream);

        /// @brief Opens the file in the specified mode.
        /// @param m The mode to open the file in.
        /// @pre The file must not already be open.
        /// @pre The file must be able to be open by the program.
        /// @post The file is open in the specified mode.
        void Open(FileMode m = FileMode::Read) override;

        /// @brief Reads data from the file into the specified field.
        ///
        /// Accepts a pointer to a binary data field and reads data from the 
        /// file at the current offset in an amount equal to the field size. 
        ///
        /// @param f The pointer to the binary data field to read into.
        /// @pre The file must be opened for reading.
        /// @pre There must be enough data remaining at the current offset.
        /// @post The offset must have advanced by field size.
        void Read(Field* f) override;

        /// @brief Writes the data in the specified field to the file.
        ///
        /// Accepts a pointer to a binary data field and writes the data from
        /// the field to the file at the current offset.
        ///
        /// @param f The pointer to the binary data field to write.
        /// @pre The file must be opened for writing.
        /// @pre The offset must be no greater than file size.
        /// @post The offset must have advanced by field size.
        void Write(Field* f) override;

        void Read(FieldStruct* s) override;

        void Write(FieldStruct* s) override;

        std::shared_ptr<ChunkHeader> FindChunkHeader(std::string ID) override;

        std::string Name() const override
        {
            return mStream->FileName();
        }

        // @brief Gets the size of the file.
        /// @return The size of the file.
        /// @pre The file must be accessible to the program.
        std::size_t Size() const override;

        /// @brief Gets the current offset (position) of the file.
        /// @return The current offset (position) of the file.
        std::size_t Offset() const override
        {
            return mStream->Offset();
        }

        /// @brief Determines if the file is currently opened.
        /// @return True if the file is open, otherwise false.
        bool IsOpen() const override
        {
            return mStream->IsOpen();
        }

        bool Exists() const override
        {
            return mStream->Exists();
        }

        /// @brief Gets the mode the file is opened in.
        /// @return The mode the file is opened in.
        FileMode Mode() const override
        {
            return mStream->Mode();
        }

        /// @brief Closes the file.
        void Close() override
        {
            mStream->Close();
        }

        /// @brief Sets the offset to perform the next read or write operation
        /// @param offset The offset to start the next read or write operation
        /// @pre Offset must not be greater than equal to the file size
        void SetOffset(std::size_t offset) override;
    private:
        std::string mName;
        std::shared_ptr<FileStream> mStream;

        bool IsOpenForReading();

        bool IsOpenForWriting();
    };
}

#endif