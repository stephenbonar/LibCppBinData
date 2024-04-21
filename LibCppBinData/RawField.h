// RawFied.h - Declares the RawField class.
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

#ifndef BIN_DATA_H
#define BIN_DATA_H

#include <cstddef>
#include <cstring>
#include <string>
#include <memory>
#include "Field.h"
#include "Format.h"

namespace BinData
{
    extern const char* rawFieldFormatError;

    class RawField : public Field
    {
    public:
        /// @brief Constructs a new RawField.
        /// @param size The size of the RawField, in bytes.
        /// @pre The size must be greater than or equal to minFieldSize.
        RawField(std::size_t size);

        RawField(const RawField& f);

        RawField(RawField&& f);

        RawField& operator=(const RawField& f);

        RawField& operator=(RawField&& f);

        /// @brief Gets the size of the field, in bytes.
        /// @return The size of the raw field, in bytes.
        std::size_t Size() const override
        {
            return mSize;
        }

        /// @brief Gets a string representation in the default format.
        ///
        /// Returns a string representation of the data in the default format,
        /// which is StringFormat::Hex for RawFields.
        ///
        /// @return A hexadecimal string representation of the data.
        std::string ToString() const override;

        /// @brief Gets a string representation in the specified format.
        ///
        /// Returns a string representation of the data in the specified 
        /// format, which can be Bin, Hex, or Ascii.
        ///
        /// @param f The format to use when converting to the string.
        /// @return A string representation in the specified format.
        /// @pre The format must not be Dec, as that is reseved for IntField.
        std::string ToString(Format f) const override;

        /// @brief Gets a raw pointer to the underlying data.
        ///
        /// This interface is intended for use with legacy APIs that need to
        /// work with the raw data. The delete[] instruction should not be 
        /// called on this pointer, nor should it be dereferenced once the
        /// RawField has been destroyed or goes out of scope.
        ///
        /// @return The raw pointer to the underlying data.
        char* Data() override
        {
            return mData.get();
        }

        friend std::ostream& operator<<(std::ostream& os, const RawField& f);
    protected:
        Format defaultFormat;
    private:
        std::unique_ptr<char[]> mData;
        std::size_t mSize;
    };
}

#endif
