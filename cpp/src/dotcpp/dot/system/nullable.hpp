/*
Copyright (C) 2015-present The DotCpp Authors.

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

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

#pragma once

#include <optional>
#include <dot/declare.hpp>
#include <dot/system/bool.hpp>
#include <dot/system/int.hpp>
#include <dot/system/long.hpp>
#include <dot/system/double.hpp>
#include <dot/system/object.hpp>
#include <dot/system/to_string.hpp>

namespace dot
{
    /// Represents a value type that can be assigned null.
    template <class T>
    class nullable : public std::optional<T>
    {
        typedef nullable self;
        typedef std::optional<T> base;

    public: // PROPERTIES

        typedef T value_type;

        /// Gets the value of the current nullable object
        /// if it has been assigned a valid underlying value.
        T value() const { return base::value(); }

        /// Gets a value indicating whether the current nullable
        /// object has a valid value of its underlying type.
        bool has_value() const { return base::has_value(); }

    public: // CONSTRUCTORS

        /// Default constructor of nullable.
        nullable() = default;

        /// Construct nullable from nullptr.
        nullable(nullptr_t) {}

        /// Initializes a new instance of the nullable
        /// structure to the specified value.
        nullable(const T& value) : base(value) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed T.
        /// Null object becomes empty nullable.
        explicit nullable(object rhs) { if (!rhs.is_empty()) *this = (T) rhs; }

        /// Copy constructor.
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.
        T value_or_default() const { return value_or_default(T()); }

        /// Retrieves the value of the current nullable<T> object,
        /// or the specified default value.
        T value_or_default(T default_value) const { return value_or(default_value); }

    public: // OPERATORS

        /// Defines an explicit conversion of a nullable
        /// instance to its underlying value.
        explicit operator T() const { return value(); }

        nullable& operator=(nullptr_t) { this->reset(); return *this; }

        bool operator==(nullptr_t) const { return !this->has_value(); }
        bool operator!=(nullptr_t) const { return this->has_value(); }

        bool operator==(T rhs) const { return value_or_default() == rhs; }
        bool operator==(nullable<T> rhs) const { return value_or_default() == rhs.value_or_default(); }
    };

    /// Helper class to implement to_string(value) via template specialization
    template <class T>
    struct to_string_impl<nullable<T>>
    {
        /// Convert value to string; for empty or null values, return string::empty.
        static string to_string(const nullable<T>& value)
        {
            if (value == nullptr)
            {
                return string::empty;
            }
            else
            {
                T inner_value = value.value();
                return to_string_impl<T>::to_string(inner_value);
            }
        }
    };

    /// Wrapper for bool where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native bool type.
    template <>
    class nullable<bool>
    {
        typedef nullable self;

    private:
        int value_ = bool_impl::empty;

    public: // PROPERTIES

        typedef bool value_type;

        /// Convert to native bool, error if the object is in uninitialized (empty) state.
        bool value() const
        {
            switch (value_)
            {
                case 1: return true;
                case 0: return false;
                case bool_impl::empty: throw std::runtime_error("Bool value is empty");
                default: throw std::runtime_error("Unknown internal value in nullable<bool>.");
            }
        }

        /// Returns true if the object is in uninitialized (empty) state.
        bool has_value() const { return value_ != bool_impl::empty; }

    public: // CONSTRUCTORS

        /// Creates in uninitialized (empty) state.
        nullable() : value_(bool_impl::empty) {}

        /// Create from native bool.
        nullable(bool value) : value_(value ? 1 : 0) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed boolean.
        /// Null object becomes empty nullable.
        explicit nullable(object rhs) { if (!rhs.is_empty()) *this = (bool) rhs; }

        /// Copy constructor.
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.
        bool value_or_default() const { return value_or_default(bool()); }

        /// Retrieves the value of the current nullable<T> object,
        /// or the specified default value.
        bool value_or_default(bool default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// Convert to native bool, error if the object is in uninitialized (empty) state.
        explicit operator bool() const { return value(); }

        /// Assign native bool.
        nullable& operator=(bool rhs) { value_ = rhs ? 1 : 0; return *this; }
    };

    /// Wrapper for int where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native int type.
    template <>
    class nullable<int>
    {
        typedef nullable self;

    private:
        int value_ = int_impl::empty;

    public: // PROPERTIES

        typedef int value_type;

        /// Convert to native double, error if the object is in uninitialized (empty) state.
        int value() const { if (value_ == int_impl::empty) throw std::runtime_error("Int value is empty"); return value_; }

        /// Returns true if the object is in uninitialized (empty) state.
        bool has_value() const { return value_ != int_impl::empty; }

    public: // CONSTRUCTORS

        /// Creates in uninitialized (empty) state.
        nullable() : value_(int_impl::empty) {}

        /// Create from native int.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        nullable(int value) : value_(value) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed int.
        /// Null object becomes empty nullable.
        explicit nullable(object rhs) { if (!rhs.is_empty()) *this = (int) rhs; }

        /// Copy constructor.
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.
        int value_or_default() const { return value_or_default(int()); }

        /// Retrieves the value of the current nullable<T> object,
        /// or the specified default value.
        int value_or_default(int default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// Convert to native int, error if the object is in uninitialized (empty) state.
        explicit operator int() const { return value(); }

        /// Assign native int.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        nullable& operator=(int rhs) { value_ = rhs; return *this; }
    };

    /// Wrapper for int64_t where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native long type.
    template <>
    class nullable<int64_t>
    {
        typedef nullable self;

    private:
        int64_t value_ = long_impl::empty;

    public: // PROPERTIES

        typedef int64_t value_type;

        /// Convert to native long, error if the object is in uninitialized (empty) state.
        int64_t value() const { if (value_ == long_impl::empty) throw std::runtime_error("long_impl value is empty"); return value_; }

        /// Returns true if the object is in uninitialized (empty) state.
        bool has_value() const { return value_ != long_impl::empty; }

    public: // CONSTRUCTORS

        /// Creates in uninitialized (empty) state.
        nullable() : value_(long_impl::empty) {}

        /// Create from native long.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        nullable(int64_t value) : value_(value) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed long.
        /// Null object becomes empty nullable.
        explicit nullable(object rhs) { if (!rhs.is_empty()) *this = (int64_t) rhs; }

        /// Copy constructor.
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.
        int64_t value_or_default() const { return value_or_default(int64_t()); }

        /// Retrieves the value of the current nullable<T> object,
        /// or the specified default value.
        int64_t value_or_default(int64_t default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// Convert to native long, error if the object is in uninitialized (empty) state.
        explicit operator int64_t() const { return value(); }

        /// Assign native long.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        nullable& operator=(int64_t rhs) { value_ = rhs; return *this; }
    };

    /// nullable double is initialized to null (empty) by default ctor.
    /// Conversion to double when in null state results in an error.
    ///
    /// This class uses a sentinel to represent null (empty) state,
    /// ensuring no size overhead compared to the native double type.
    template <>
    class nullable<double>
    {
        typedef nullable self;

    private:
        double value_ = double_impl::empty;

    public: // PROPERTIES

        typedef double value_type;

        /// Convert to native double, error if the object is in null (empty) state.
        double value() const { if (value_ == double_impl::empty) throw std::runtime_error("Double value is empty"); return value_; }

        /// Returns true if the object is in uninitialized (empty) state.
        bool has_value() const { return value_ != double_impl::empty; }

    public: // CONSTRUCTORS

        /// Creates in uninitialized (empty) state.
        nullable() : value_(double_impl::empty) {}

        /// Create from native double.
        ///
        /// If sentinel value for null state is passed to this constructor,
        /// no error occurs and the object is constructed in null state.
        nullable(double value) : value_(value) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed double.
        /// Null object becomes empty nullable.
        explicit nullable(object rhs) { if (!rhs.is_empty()) *this = (double) rhs; }

        /// Copy constructor.
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.
        double value_or_default() const { return value_or_default(double()); }

        /// Retrieves the value of the current nullable<T> object,
        /// or the specified default value.
        double value_or_default(double default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// Convert to native double, error if the object is in null (empty) state.
        explicit operator double() const { return value(); }

        /// Assign native double.
        ///
        /// If sentinel value for null state is passed to this operator,
        /// no error occurs and the object reverts to null (empty) state.
        nullable& operator=(double rhs) { value_ = rhs; return *this; }

        bool operator ==(double rhs) const { return value_ == rhs; }
        bool operator ==(nullable<double> rhs) const { return value_ == rhs.value_or_default(); }

    };
}
