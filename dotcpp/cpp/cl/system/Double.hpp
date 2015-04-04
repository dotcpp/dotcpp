/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp (.C++), an open source implementation of
selected .NET class library APIs in native C++ with optional support
for algorithmic differentiation (AD), available from

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __cl_system_Double_hpp__
#define __cl_system_Double_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/DoubleConverter.hpp>

namespace cl
{
    //!! Replace by header inclusion or avoid returning by value
    struct String {};

    /// <summary>Immutable double type with AD support designed
    /// to serve as a drop-in replacement to native double.</summary>
    class CL_SYSTEM CppDouble
    {
        /// <summary>Returns the result of addition of two Double objects.</summary>
        friend inline CppDouble operator+(const CppDouble& lhs, const CppDouble& rhs) { return lhs.value_ + rhs.value_; }

        /// <summary>Returns the result of subtraction of two Double objects.</summary>
        friend inline CppDouble operator-(const CppDouble& lhs, const CppDouble& rhs) { return lhs.value_ - rhs.value_; }

        /// <summary>Returns the result of multiplication of two Double objects.</summary>
        friend inline CppDouble operator*(const CppDouble& lhs, const CppDouble& rhs) { return lhs.value_ * rhs.value_; }

        /// <summary>Returns the result of division of two Double objects.</summary>
        friend inline CppDouble operator/(const CppDouble& lhs, const CppDouble& rhs) { return lhs.value_ / rhs.value_; }

        /// <summary>Returns the result of addition of Double and double.</summary>
        friend inline CppDouble operator+(const CppDouble& lhs, double rhs) { return lhs.value_ + rhs; }

        /// <summary>Returns the result of subtraction of Double and double.</summary>
        friend inline CppDouble operator-(const CppDouble& lhs, double rhs) { return lhs.value_ - rhs; }

        /// <summary>Returns the result of multiplication of Double and double.</summary>
        friend inline CppDouble operator*(const CppDouble& lhs, double rhs) { return lhs.value_ * rhs; }

        /// <summary>Returns the result of division of Double and double.</summary>
        friend inline CppDouble operator/(const CppDouble& lhs, double rhs) { return lhs.value_ / rhs; }

        /// <summary>Returns the result of addition of double and Double.</summary>
        friend inline CppDouble operator+(double lhs, const CppDouble& rhs) { return lhs + rhs.value_; }

        /// <summary>Returns the result of subtraction of double and Double.</summary>
        friend inline CppDouble operator-(double lhs, const CppDouble& rhs) { return lhs - rhs.value_; }

        /// <summary>Returns the result of multiplication of double and Double.</summary>
        friend inline CppDouble operator*(double lhs, const CppDouble& rhs) { return lhs * rhs.value_; }

        /// <summary>Returns the result of division of double and Double.</summary>
        friend inline CppDouble operator/(double lhs, const CppDouble& rhs) { return lhs / rhs.value_; }

        /// <summary>Returns true if lhs is equal to rhs.</summary>
        friend inline bool operator==(double lhs, const CppDouble& rhs) { return lhs == rhs.value_; }

        /// <summary>Returns true if lhs is not equal to rhs.</summary>
        friend inline bool operator!=(double lhs, const CppDouble& rhs) { return lhs != rhs.value_; }

        /// <summary>Returns true if lhs is less than rhs.</summary>
        friend inline bool operator<(double lhs, const CppDouble& rhs) { return lhs < rhs.value_; }

        /// <summary>Returns true if lhs is less than or equal to rhs.</summary>
        friend inline bool operator<=(double lhs, const CppDouble& rhs) { return lhs <= rhs.value_; }

        /// <summary>Returns true if lhs is more than rhs.</summary>
        friend inline bool operator>(double lhs, const CppDouble& rhs) { return lhs > rhs.value_; }

        /// <summary>Returns true if lhs is more than or equal to rhs.</summary>
        friend inline bool operator>=(double lhs, const CppDouble& rhs) { return lhs >= rhs.value_; }

        /// <summary>Serialize to stream.</summary>
        friend inline std::ostream& operator<<(std::ostream& output, const CppDouble& value) { output << value.value_; return output; }

        /// <summary>Deserialize from stream.</summary>
        friend inline std::istream& operator>>(std::istream& input, CppDouble& value) { input >> value.value_; return input; }

    private:

        /// <summary> The friend class to conversations </summary>
        template <typename, typename, typename, typename, typename, typename, typename, typename >
        friend struct cl::DoubleConvert;

    public: // TYPEDEFS

        /// <summary>Backend-specific AD implementation type,
        /// name using this library's naming conventions.</summary>
        typedef double ImplType;

        /// <summary>Backend-specific AD implementation type,
        /// name using required STL naming conventions.</summary>
        typedef ImplType value_type;

        /// <summary>Explicit constructor attempts to convert from any type.</summary>
        template <typename Type>
        explicit CppDouble(Type const& rhs)
            : value_()
        {
            cl::DoubleConvert<Type, value_type>::convert(*this, rhs);
        }

        /// <summary>Assignment from other type.</summary>
        template <typename Type>
        inline CppDouble& operator=(Type const& rhs)
        {
            cl::DoubleConvert<Type, value_type>::convert(*this, rhs);
            return *this;
        }

    private: // PRIVATE

        /// <summary>Return cast value is it's arithmetic.</summary>
        template <typename Type>
        inline Type get__(std::true_type, std::false_type) const
        {
#if defined CL_COMPILE_TIME_DEBUG
#   pragma message ("get__ std::true_type, std::false_type " __FUNCSIG__)
#endif
            return static_cast<Type>(ext::Value(this->value_));
        }

        template <typename Type>
        inline Type get__(std::true_type, std::true_type) const
        {
#if defined CL_COMPILE_TIME_DEBUG
#   pragma message ("get__ std::true_type, std::true_type " __FUNCSIG__)
#endif
            return static_cast<Type>(this->value_);
        }

        /// <summary>Return cast value. Try to create instance Typed.</summary>
        template <typename Type>
        inline Type get__(std::false_type, std::false_type) const
        {
#if defined CL_COMPILE_TIME_DEBUG
#   pragma message ("get__ std::false_type, std::false_type " __FUNCSIG__)
#endif
            // Would cause a recursive call
            static_assert(false, "Conversion to this type isn't implemented");
            return Type();
        }

        template <typename Type>
        inline Type get__(std::false_type, std::true_type) const
        {
#if defined CL_COMPILE_TIME_DEBUG
#   pragma message ("get__ std::false_type, std::true_type " __FUNCSIG__)
#endif
            return Type(value_);
        }
    public:

#ifndef  EXPLICIT_NATIVE_CONVERT
        // Try to convert explicit if it is arithmetic
        template <typename Type>
        inline explicit operator Type() const
        {
#if defined CL_COMPILE_TIME_DEBUG
#   pragma message ("convert compilation for: " __FUNCSIG__)
#endif
            typedef typename std::remove_volatile<typename std::remove_const<Type>::type >::type native_type;

            enum {
                is_sm = std::is_same<native_type, value_type >::value
                , is_constructible_from_value = std::is_constructible <native_type, value_type>::value
            };

            typedef std::integral_constant<bool, is_sm || is_constructible_from_value > is_value_type;

            return this->get__<Type>(std::is_arithmetic<Type>::type(), is_value_type());
        }
#else
        inline explicit operator int() const { return (int)value_; }
        inline explicit operator value_type() const { return value_; }
        inline explicit operator unsigned int() const { return (unsigned int)value_; }
        inline explicit operator unsigned long() const { return (unsigned long)value_; }
        inline explicit operator long() const { return (long)value_; }
#endif

    private: // FIELDS

        ImplType value_;

    public: // CONSTRUCTORS

        inline CppDouble() : value_() {}

        /// <summary>Implicit constructor from double.</summary>
        inline CppDouble(ImplType rhs) : value_(rhs) {}

    public: // METHODS

        /// <summary>Convert to string.</summary>
        String toString() const;

    public: // OPERATORS

        /// <summary>Assignment of native double.</summary>
        inline CppDouble& operator=(double rhs) { value_ = rhs; return *this; }

        /// <summary>Adds rhs to self.</summary>
        inline CppDouble& operator+=(const CppDouble& rhs) { value_ += rhs.value_; return *this; }

        /// <summary>Adds rhs to self.</summary>
        inline CppDouble& operator+=(double rhs) { value_ += rhs; return *this; }

        /// <summary>Subtracts rhs from self.</summary>
        inline CppDouble& operator-=(const CppDouble& rhs) { value_ -= rhs.value_; return *this; }

        /// <summary>Subtracts rhs from self.</summary>
        inline CppDouble& operator-=(double rhs) { value_ -= rhs; return *this; }

        /// <summary>Multiplies self by rhs.</summary>
        inline CppDouble& operator*=(const CppDouble& rhs) { value_ *= rhs.value_; return *this; }

        /// <summary>Multiplies self by rhs.</summary>
        inline CppDouble& operator*=(double rhs) { value_ *= rhs; return *this; }

        /// <summary>Divides self by rhs.</summary>
        inline CppDouble& operator/=(const CppDouble& rhs) { value_ /= rhs.value_; return *this; }

        /// <summary>Divides self by rhs.</summary>
        inline CppDouble& operator/=(double rhs) { value_ /= rhs; return *this; }

        /// <summary>Returns a copy if self.</summary>
        inline CppDouble operator+() const { return CppDouble(value_); }

        /// <summary>Returns the negative of self.</summary>
        inline CppDouble operator-() const { return CppDouble(-value_); }

        /// <summary>Returns true if self is equal to rhs.</summary>
        inline bool operator==(const CppDouble& rhs) const { return value_ == rhs.value_; }

        /// <summary>Returns true if self is equal to rhs.</summary>
        inline bool operator==(double rhs) const { return value_ == rhs; }

        /// <summary>Returns true if self is not equal to rhs.</summary>
        inline bool operator!=(const CppDouble& rhs) const { return value_ != rhs.value_; }

        /// <summary>Returns true if self is not equal to rhs.</summary>
        inline bool operator!=(double rhs) const { return value_ != rhs; }

        /// <summary>Returns true if self is less than rhs.</summary>
        inline bool operator<(const CppDouble& rhs) const { return value_ < rhs.value_; }

        /// <summary>Returns true if self is less than rhs.</summary>
        inline bool operator<(double rhs) const { return value_ < rhs; }

        /// <summary>Returns true if self is less than or equal to rhs.</summary>
        inline bool operator<=(const CppDouble& rhs) const { return value_ <= rhs.value_; }

        /// <summary>Returns true if self is less than or equal to rhs.</summary>
        inline bool operator<=(double rhs) const { return value_ <= rhs; }

        /// <summary>Returns true if self is more than rhs.</summary>
        inline bool operator>(const CppDouble& rhs) const { return value_ > rhs.value_; }

        /// <summary>Returns true if self is more than rhs.</summary>
        inline bool operator>(double rhs) const { return value_ > rhs; }

        /// <summary>Returns true if self is more than or equal to rhs.</summary>
        inline bool operator>=(const CppDouble& rhs) const { return value_ >= rhs.value_; }

        /// <summary>Returns true if self is more than or equal to rhs.</summary>
        inline bool operator>=(double rhs) const { return value_ >= rhs; }

    private:

        template <typename Type>
        inline static ImplType
        Value(Type const& obj, std::true_type) { return obj.value_; }

        template <typename Type>
        inline static ImplType
        Value(Type const& obj, std::false_type) { return static_cast<ImplType>(obj); }
    };
}

#endif  // __cl_system_Double_hpp__
