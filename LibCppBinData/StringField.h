// StringField.h - Declares the StringField class.
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

#ifndef BIN_DATA_STRING_FIELD_H
#define BIN_DATA_STRING_FIELD_H

#include <cstddef>
#include <string>
#include "RawField.h"

namespace BinData
{
    class StringField : public RawField
    {
    public:
        /// @brief Constructs a new StringField.
        /// @param size The size of the StringField, in bytes.
        /// @pre The size must be greater than or equal to minFieldSize.
        StringField(std::size_t size) : RawField(size) { }

        StringField(std::string data, std::size_t size) : RawField(size) 
        { 
            SetData(data);
        }

        StringField(const StringField& f) : RawField{ f } { }

        StringField(StringField&& f) : RawField{ std::move(f) } { }

        StringField& operator=(const StringField& f)
        {
            RawField::operator=(f);
            return *this;
        }

        StringField& operator=(StringField&& f)
        {
            RawField::operator=(std::move(f));
            return *this;
        }

        /// @brief Gets a string representation in the default format.
        ///
        /// Returns a string representation of the data in the default format,
        /// which is StringFormat::Ascii for StringFields. The ASCII 
        /// format includes all printable characters and replaces all 
        /// non-printable characters with a period.
        ///
        /// @return An ASCII string representation of the data.
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

        /// @brief Sets the data to the specified string.
        ///
        /// Copies the ASCII characters from the specified string into the
        /// field's data. If the specified string is smaller than the field,
        /// the remaining elements will be null characters. If the specified
        /// string is larger than the data field, the specified string will
        /// be truncated to fit the size of the field.
        ///
        /// @param s The string to copy into the field.
        void SetData(std::string s);
    };
}

#endif