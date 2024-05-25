// File.h - Declares the File class.
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

#ifndef BIN_DATA_FILE_H
#define BIN_DATA_FILE_H

#include <cstddef>
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <memory>
#include "Field.h"
#include "FileStream.h"
#include "FieldStruct.h"
#include "ChunkHeader.h"

namespace BinData
{
    class InvalidFile : public std::invalid_argument
    {
    public:
        /// @brief Constructs an InvalidFileOperation exception.
        /// @param message The error message to include with the exception.
        InvalidFile(const char* message) : std::invalid_argument(message) { }
    };

    class InvalidFileOperation : public std::logic_error
    {
    public:
        /// @brief Constructs an InvalidFileOperation exception.
        /// @param message The error message to include with the exception.
        InvalidFileOperation(const char* message) : std::logic_error(message) { }
    };

    class File
    {
    public:
        /// @brief Opens the file in the specified mode.
        /// @param m The mode to open the file in.
        /// @pre The file must not already be open.
        /// @pre The file must be able to be open by the program.
        /// @post The file is open in the specified mode.
        virtual void Open(FileMode m = FileMode::Read) = 0;

        /// @brief Reads data from the file into the specified field.
        ///
        /// Accepts a pointer to a binary data field and reads data from the 
        /// file at the current offset in an amount equal to the field size. 
        ///
        /// @param f The pointer to the binary data field to read into.
        /// @pre The file must be opened for reading.
        /// @pre There must be enough data remaining at the current offset.
        /// @post The offset must have advanced by field size.
        virtual void Read(Field* f) = 0;

        /// @brief Writes the data in the specified field to the file.
        ///
        /// Accepts a pointer to a binary data field and writes the data from
        /// the field to the file at the current offset.
        ///
        /// @param f The pointer to the binary data field to write.
        /// @pre The file must be opened for writing.
        /// @pre The offset must be no greater than file size.
        /// @post The offset must have advanced by field size.
        virtual void Write(Field* f) = 0;

        virtual void Read(FieldStruct* s) = 0;

        virtual void Write(FieldStruct* s) = 0;

        virtual ChunkHeader FindChunkHeader(std::string ID) = 0;

        virtual std::string Name() const = 0;

        // @brief Gets the size of the file.
        /// @return The size of the file.
        /// @pre The file must be accessible to the program.
        virtual std::size_t Size() const = 0;

        /// @brief Gets the current offset (position) of the file.
        /// @return The current offset (position) of the file.
        virtual std::size_t Offset() const = 0;

        /// @brief Determines if the file is currently opened.
        /// @return True if the file is open, otherwise false.
        virtual bool IsOpen() const = 0;

        virtual bool Exists() const = 0;

        /// @brief Gets the mode the file is opened in.
        /// @return The mode the file is opened in.
        virtual FileMode Mode() const = 0;

        /// @brief Closes the file.
        virtual void Close() = 0;

        /// @brief Sets the offset to perform the next read or write operation
        /// @param offset The offset to start the next read or write operation
        /// @pre Offset must not be greater than equal to the file size
        virtual void SetOffset(std::size_t offset) = 0;
    };
}

#endif