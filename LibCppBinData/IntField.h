// IntField.h - Declares the IntField class.
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

#ifndef BIN_DATA_INT_FIELD_H
#define BIN_DATA_INT_FIELD_H

#include <cstddef>
#include <cstring>
#include <memory>
#include <sstream>
#include <limits>
#include <iostream>
#include "Field.h"
#include "Format.h"
#include "IntConstants.h"

namespace BinData
{   
    extern const char* intFieldFormatError;

    enum class FieldEndianness
    {
        Little,
        Big
    };

    // We need to forward declare both the class template and its operator<<
    // to allow both templates to recognize each other.
    template<typename ValueType, std::size_t size>
    class IntField;
    template<typename ValueType, std::size_t size>
    std::ostream& operator<<(std::ostream& os, const IntField<ValueType, size>& f);

    template<typename ValueType, std::size_t size>
    class IntField : public Field
    {
    public:
        IntField(FieldEndianness endianness = FieldEndianness::Little) 
            : mEndianness{ endianness }
        {
            mData = std::make_unique<char[]>(size);
        }

        IntField(ValueType value, 
            FieldEndianness endianness = FieldEndianness::Little)
            : mEndianness{ endianness }
        {
            mData = std::make_unique<char[]>(size);
            SetValue(value);
        }

        IntField(const IntField& f)
        {
            mData = std::make_unique<char[]>(size);
            std::memcpy(mData.get(), f.mData.get(), size);
            mEndianness = f.mEndianness;
        }

        IntField(IntField&& f)
        {
            mData = std::move(f.mData);
            mEndianness = f.mEndianness;
        }

        IntField& operator=(const IntField& f)
        {
            auto copiedData = std::make_unique<char[]>(size);
            std::memcpy(copiedData.get(), f.mData.get(), size);
            mData = std::move(copiedData);
            mEndianness = f.mEndianness;
            return *this;
        }

        IntField& operator=(IntField&& f)
        {
            mData = std::move(f.mData);
            mEndianness = f.mEndianness;
            return *this;
        }

        FieldEndianness Endianness() const
        {
            return mEndianness;
        }

        /// @brief Gets the size of the field, in bytes.
        /// @return The size of the raw field, in bytes.
        std::size_t Size() const override
        {
            return size;
        }

        /// @brief Gets the value of the data as a native integer type.
        ///
        /// This function reads the raw bytes representing an integer
        /// value into a native integer type. It interprets the value as if it
        /// were the same endianness as the current system. If the data in the
        /// field is the opposite of the current system's endianess, then use
        /// ValueOtherEndian().
        ///
        /// @return The value of the data as a native integer type.
        ValueType Value() const
        {
            if (mData == nullptr)
                throw InvalidField{ nullFieldError };
            if (mEndianness == FieldEndianness::Little)
                return ValueLEToLE();
            else
                return ValueBEToLE();

            // TODO: On big endian systems, disable the above code and enable
            // the code below:
            // if (mEndianness == BinData::FieldEndianness::Big)
            //     return ValueBEToBE();
            // else
            //     return ValueLEToBE();
        }

        /// @brief Gets a string representation in the default format.
        ///
        /// Returns a string representation of the data in the default format,
        /// which is StringFormat::Dec for IntFields.
        ///
        /// @return A decimal string representation of the data.
        std::string ToString() const override
        {
            std::stringstream s;
            s << Value();
            return s.str();
        }

        /// @brief Gets a string representation in the specified format.
        ///
        /// Returns a string representation of the data in the specified 
        /// format, which can be Bin, Hex, Dec.
        ///
        /// @param f The format to use when converting to the string.
        /// @return A string representation in the specified format.
        /// @pre Format must be Bin, Hex, or Dec.
        /// @throw InvalidFormat when an invalid format is specified.
        std::string ToString(Format f) const override
        {
            if (mData == nullptr)
                throw InvalidField{ nullFieldError };
            switch(f)
            {
                case Format::Hex:
                    return FormatHex(mData.get(), size);
                case Format::Bin:
                    return FormatBin(mData.get(), size);
                case Format::Dec:
                    return ToString();
                case Format::Ascii:
                    throw InvalidFormat{ intFieldFormatError };
                default:
                    return ToString();
            }
        }

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

        /*
        /// @brief Gets the value of the data as a native integer type.
        ///
        /// Use this variation of the Value() method when the data in the field
        /// is the opposite endianness of the current system.
        ///
        /// @return The value of the data as a native integer type.
        ValueType ValueOppositeEndianness() const
        {
            // If platform is little endian
            return ValueBEToLE();

            // TODO: Else if platform is big endian
            //return ValueLEToBE();
        }*/

        void SetEndianness(FieldEndianness endianness)
        {
            mEndianness = endianness;
        }

        /// @brief Sets the field to the value of the specified integer.
        ///
        /// The specified integer value is stored as raw bytes in the
        /// data field with the same endianness of the current system.
        /// If the data should be set in the opposite endianness, use
        /// SetValueOtherEndian().
        ///
        /// @param v The value to set the field to.
        void SetValue(ValueType v)
        {
            if (mData != nullptr)
            {
                if (mEndianness == FieldEndianness::Little)
                    SetValueLEToLE(v);
                else
                    SetValueLEToBE(v);
            }
            else
                throw InvalidField{ nullFieldError };

            // TODO: On big endian systems, disable the above code and enable
            // the code below:
            // if (mEndianness == BigData::FieldEndianness::Big)
            //     SetValueBEToBE(v);
            // else
            //     SetValueBEToLE(v);
        }

        /*
        /// @brief Sets the field to the value of the specified integer.
        ///
        /// Use this variation of the SetValue() method when the data in the
        /// field needs to be stored in the opposite endianness of the current
        /// system.
        ///
        /// @param v The value to set the field to.
        void SetValueOppositeEndianness(ValueType v)
        {
            SetValueLEToBE(v);
        }*/
    //protected:
    //    Format defaultFormat;
    private:
        std::unique_ptr<char[]> mData;
        FieldEndianness mEndianness;

        // Call this function when the data is stored in little endian format
        // and the system has little endian integers . 
        ValueType ValueLEToLE() const
        {
            // To convert raw bytes to native integer types, we will use
            // bit shifts and bitwise or on each byte to get it into the
            // result integer while not circumventing the type system or
            // having to guess what type of integer to use. While loading the
            // individual bytes into the long long result integer, we want to
            // keep everything unsigned so there are no unexpected sign 
            // conversions / overflows. We use the largest available integer
            // type so we can handle all possible result sizes with the same 
            // code.
            unsigned long long result = 0;

            // We have to do some extra work if this IntField is signed and
            // the value is negative: if the field size is less than the
            // result size (likely true for all field sizes less than 
            // Int64Field), we need to set the unused most significant bytes 
            // to 0xFF to ensure the result is interpreted as 2's compliment.
            bool signBitSet = (mData[size - 1] & signBitMask) == signBitMask;
            if (std::numeric_limits<ValueType>::is_signed && signBitSet)
                result = GetSignBitPaddingLE();
    
            for (int i = 0; i < size; i++)
            {
                // We are assuming the raw data is little endian so we start with
                // no byte shifts at first when i = 0, but then we'll shift the 
                // next byte one position (i = 1), etc.
                unsigned int bitsToShift = i * bitsPerByte;

                // Convert the byte to unsigned to avoid any implicit sign
                // conversion.
                unsigned char currentByte = static_cast<unsigned char>(
                    mData[i]);

                // Copy the currentByte into another unsigned long long to 
                // match result so they can be bitwise or'd together without
                // any accidental promotion, sign conversion, etc.
                unsigned long long valueToShift = currentByte;

                unsigned long long shiftedValue = valueToShift << bitsToShift;

                // Bitwise or the shifted value with the result to combine the 
                // shifted bits with the existing result. To use an example, if
                // we were converting the little endian representation of 
                // 42,000,000, which would be:
                //
                // Hex: 0x80 0xDE 0x80 0x02
                // Bin: 10000000 11011110 10000000 00000010
                //
                // Each iteration would do the following:
                //
                // First iteration:
                // result        : 00000000 00000000 00000000 00000000
                // | shiftedByte : 10000000 00000000 00000000 00000000
                //                 -----------------------------------
                // result        : 10000000 00000000 00000000 00000000
                //
                // Second iteration:
                // result        : 10000000 00000000 00000000 00000000
                // | shiftedByte : 00000000 11011110 00000000 00000000
                //                 -----------------------------------
                // result        : 10000000 11011110 00000000 00000000
                //
                // Third iteration:
                // result        : 10000000 11011110 00000000 00000000
                // | shiftedByte : 00000000 00000000 10000000 00000000
                //                 -----------------------------------
                // result        : 10000000 11011110 10000000 00000000
                //
                // Fourth iteration:
                // result        : 10000000 11011110 10000000 00000000
                // | shiftedByte : 00000000 00000000 00000000 00000010
                //                 -----------------------------------
                // result        : 10000000 11011110 10000000 00000010
                result = result | shiftedValue;
            }

            // After the unsigned bits have been transferred to the result 
            // integer, we can finally convert the result to whatever the
            // IntField's ValueType is, signed or unsigned, without losing
            // information.
            return static_cast<ValueType>(result);
        }

        // Call this function when the data is stored in big endian format
        // but the system has little endian integers.
        ValueType ValueBEToLE() const
        {
            // To convert raw bytes to native integer types, we will use
            // bit shifts and bitwise or on each byte to get it into the
            // result integer while not circumventing the type system or
            // having to guess what type of integer to use. While loading the
            // individual bytes into the long long result integer, we want to
            // keep everything unsigned so there are no unexpected sign 
            // conversions / overflows. We use the largest available integer
            // type so we can handle all possible result sizes with the same 
            // code.
            unsigned long long result = 0;

            // We have to do some extra work if this IntField is signed and
            // the value is negative: if the field size is less than the
            // result size (likely true for all field sizes less than 
            // Int64Field), we need to set the unused most significant bytes 
            // to 0xFF to ensure the result is interpreted as 2's compliment.
            bool signBitSet = (mData[0] & signBitMask) == signBitMask;
            if (std::numeric_limits<ValueType>::is_signed && signBitSet)
                result = GetSignBitPaddingLE();
            
            int bytesToShift = size - 1;
            for (int i = 0; i < size; i++)
            {
                unsigned int bitsToShift = bytesToShift * bitsPerByte;

                // Convert the byte to unsigned to avoid any implicit sign
                // conversion.
                unsigned char currentByte = static_cast<unsigned char>(
                    mData[i]);

                // Copy the currentByte into another unsigned long long to 
                // match result so they can be bitwise or'd together without
                // any accidental promotion, sign conversion, etc.
                unsigned long long valueToShift = currentByte;

                unsigned long long shiftedValue = valueToShift << bitsToShift;

                // Bitwise or the shifted value with the result to combine the 
                // shifted bits with the existing result. To use an example, if
                // we were converting the big endian representation of 
                // 42,000,000, which would be:
                //
                // Hex: 0x02 0x80 0xDE 0x80
                // Bin: 00000010 10000000 11011110 10000000
                //
                // Each iteration would do the following:
                //
                // First iteration:
                // result        : 00000000 00000000 00000000 00000000
                // | shiftedByte : 00000000 00000000 00000000 00000010
                //                 -----------------------------------
                // result        : 00000000 00000000 00000000 00000010
                //
                // Second iteration:
                // result        : 00000000 00000000 00000000 00000010
                // | shiftedByte : 00000000 00000000 10000000 00000000
                //                 -----------------------------------
                // result        : 00000000 00000000 10000000 00000010
                //
                // Third iteration:
                // result        : 00000000 00000000 10000000 00000010
                // | shiftedByte : 00000000 11011110 00000000 00000000
                //                 -----------------------------------
                // result        : 00000000 11011110 10000000 00000010
                //
                // Fourth iteration:
                // result        : 00000000 11011110 10000000 00000010
                // | shiftedByte : 10000000 00000000 00000000 00000000
                //                 -----------------------------------
                // result        : 10000000 11011110 10000000 00000010
                result = result | shiftedValue;

                bytesToShift--;
            }

            // After the unsigned bits have been transferred to the result 
            // integer, we can finally convert the result to whatever the
            // IntField's ValueType is, signed or unsigned, without losing
            // information.
            return static_cast<ValueType>(result);
        }

        // Call this function when the system's integers are litte endian.
        unsigned long long GetSignBitPaddingLE() const
        {
            unsigned long long resultPadding = 0;

            // We need to know how big the result size is to know how
            // many extra bytes we need to set to the padding value of 
            // 0xFF. Although it should be at least 64-bits per the 
            // standard, it may be 128-bits on some platforms.
            int resultSize = sizeof(unsigned long long);

            // The first 0xFF will need to be shifted into the most 
            // significant byte, which is n-1 bytes to shift.
            unsigned int bytesToShift = resultSize - 1;

            // Start at the result size but decrease until we're at the
            // same size as the IntField so we know when to stop padding
            // the result with 0xFF.
            for (int i = resultSize; i > size; i--)
            {
                unsigned int bitsToShift = bytesToShift * bitsPerByte;

                // Even though we're just shifting a single byte value into
                // place, we store the padding value straight into an
                // unsigned long long so it is exactly the same size as 
                // result with no risk of accidental sign conversion, etc.
                // Esentially looks like this if long long is 64-bit little
                // endian:
                // FF 00 00 00 00 00 00 00 
                unsigned long long padding{ 0xFF };

                // Assuming 64-bit little endian, if padding was shifted on
                // the first pass:  00 00 00 00 00 00 00 FF
                // second pass:     00 00 00 00 00 00 FF 00, etc.
                padding = padding << bitsToShift;

                // Bitwise or the padding with the result to combine each 
                // pass of the padding byte shift into the result:
                // result on first pass:  00 00 00 00 00 00 00 FF
                // result on second pass: 00 00 00 00 00 00 FF FF, etc.
                resultPadding = resultPadding | padding;

                bytesToShift--;
            }

            return resultPadding;
        }

        void SetValueLEToLE(ValueType v)
        {
            constexpr unsigned long long bitMask{ 0xFF };
            auto value = static_cast<unsigned long long>(v);
            for (int i = 0; i < size; i++)
            {
                unsigned int bitsToShift = i * bitsPerByte;
                unsigned long long shiftedBitMask = bitMask << bitsToShift;
                unsigned long long byte = value & shiftedBitMask;
                unsigned long long shiftedByte = byte >> bitsToShift;
                mData[i] = static_cast<char>(shiftedByte);
            }
        }

        void SetValueLEToBE(ValueType v)
        {
            constexpr unsigned long long bitMask{ 0xFF };
            auto value = static_cast<unsigned long long>(v);
            unsigned int bytesToShift = size - 1;
            for (int i = 0; i < size; i++)
            {
                unsigned int bitsToShift = bytesToShift * bitsPerByte;
                unsigned long long shiftedBitMask = bitMask << bitsToShift;
                unsigned long long byte = value & shiftedBitMask;
                unsigned long long shiftedByte = byte >> bitsToShift;
                mData[i] = static_cast<char>(shiftedByte);
                bytesToShift--;
            }
        }

        friend std::ostream& operator<< <>(std::ostream& os, const IntField<ValueType, size>& f);
    };

    template<typename ValueType, std::size_t size>
    std::ostream& operator<<(std::ostream& os, const IntField<ValueType, size>& f)
    {
        os << f.Value();
        return os;
    }

    using UInt8Field = IntField<unsigned int, 1>;
    using UInt16Field = IntField<unsigned int, 2>;
    using UInt24Field = IntField<unsigned long, 3>;
    using UInt32Field = IntField<unsigned long, 4>;
    using UInt64Field = IntField<unsigned long long, 8>;

    using Int8Field = IntField<int, 1>;
    using Int16Field = IntField<int, 2>;
    using Int24Field = IntField<long, 3>;
    using Int32Field = IntField<long, 4>;
    using Int64Field = IntField<long long, 8>;
}

#endif
