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
#include <dot/system/Bool.hpp>
#include <dot/system/Int.hpp>
#include <dot/system/Long.hpp>
#include <dot/system/Double.hpp>
#include <dot/system/object.hpp>

namespace dot
{
    /// <summary>Represents a value type that can be assigned null.</summary>
    template <class T>
    class nullable : public std::optional<T>
    {
        typedef nullable self;
        typedef std::optional<T> base;

    public: // PROPERTIES

        typedef T value_type;

        /// <summary>Gets the value of the current nullable object
        /// if it has been assigned a valid underlying value.</summary>
        T value() const { return this->value(); }

        /// <summary>Gets a value indicating whether the current nullable
        /// object has a valid value of its underlying type.</summary>
        bool has_value() const { return this->has_value(); }

    public: // CONSTRUCTORS

        /// <summary>Default constructor of nullable.</summary>
        nullable() = default;

        /// <summary>Construct nullable from nullptr.</summary>
        nullable(nullptr_t) {}

        /// <summary>Initializes a new instance of the nullable
        /// structure to the specified value.</summary>
        nullable(T value) : base(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed T.
        /// Null object becomes empty nullable.
        /// </summary>
        explicit nullable(object rhs) { if (!rhs.IsEmpty()) *this = (T) rhs; }

        /// <summary>Copy constructor.</summary>
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.</summary>
        T value_or_default() const { return value_or_default(T()); }

        /// <summary>Retrieves the value of the current nullable<T> object,
        /// or the specified default value.</summary>
        T value_or_default(T default_value) const { return value_or(default_value); }

    public: // OPERATORS

        /// <summary>Defines an explicit conversion of a nullable
        /// instance to its underlying value.</summary>
        explicit operator T() const { return value(); }

        nullable& operator=(nullptr_t) { this->reset(); return *this; }

        bool operator==(nullptr_t) { return !this->has_value(); }
        bool operator!=(nullptr_t) { return this->has_value(); }

        bool operator ==(T rhs) { return value_or_default() == rhs; }
        bool operator ==(nullable<T> rhs) { return value_or_default() == rhs.value_or_default(); }
    };

    /// <summary>
    /// Wrapper for bool where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native bool type.
    /// </summary>
    template <>
    class nullable<bool>
    {
        typedef nullable self;

    private:
        int value_ = bool_impl::empty;

    public: // PROPERTIES

        typedef bool value_type;

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
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

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool has_value() const { return value_ != bool_impl::empty; }

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        nullable() : value_(bool_impl::empty) {}

        /// <summary>Create from native bool.</summary>
        nullable(bool value) : value_(value ? 1 : 0) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed boolean.
        /// Null object becomes empty nullable.
        /// </summary>
        explicit nullable(object rhs) { if (!rhs.IsEmpty()) *this = (bool) rhs; }

        /// <summary>Copy constructor.</summary>
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.</summary>
        bool value_or_default() const { return value_or_default(bool()); }

        /// <summary>Retrieves the value of the current nullable<T> object,
        /// or the specified default value.</summary>
        bool value_or_default(bool default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
        explicit operator bool() const { return value(); }

        /// <summary>Assign native bool.</summary>
        nullable& operator=(bool rhs) { value_ = rhs ? 1 : 0; return *this; }
    };

    /// <summary>
    /// Wrapper for int where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native int type.
    /// </summary>
    template <>
    class nullable<int>
    {
        typedef nullable self;

    private:
        int value_ = int_impl::empty;

    public: // PROPERTIES

        typedef int value_type;

        /// <summary>Convert to native double, error if the object is in uninitialized (empty) state.</summary>
        int value() const { if (value_ == int_impl::empty) throw std::runtime_error("Int value is empty"); return value_; }

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool has_value() const { return value_ != int_impl::empty; }

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        nullable() : value_(int_impl::empty) {}

        /// <summary>
        /// Create from native int.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        nullable(int value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed int.
        /// Null object becomes empty nullable.
        /// </summary>
        explicit nullable(object rhs) { if (!rhs.IsEmpty()) *this = (int) rhs; }

        /// <summary>Copy constructor.</summary>
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.</summary>
        int value_or_default() const { return value_or_default(int()); }

        /// <summary>Retrieves the value of the current nullable<T> object,
        /// or the specified default value.</summary>
        int value_or_default(int default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// <summary>Convert to native int, error if the object is in uninitialized (empty) state.</summary>
        explicit operator int() const { return value(); }

        /// <summary>
        /// Assign native int.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        nullable& operator=(int rhs) { value_ = rhs; return *this; }
    };

    /// <summary>
    /// Wrapper for int64_t where default constructor creates uninitialized
    /// value. Use this class to get an error message when the variable is
    /// used before being assigned to.
    ///
    /// This class uses sentinel to represent uninitialized (empty) state,
    /// ensuring no size overhead compared to the native long type.
    /// </summary>
    template <>
    class nullable<int64_t>
    {
        typedef nullable self;

    private:
        int64_t value_ = long_impl::empty;

    public: // PROPERTIES

        typedef int64_t value_type;

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        int64_t value() const { if (value_ == long_impl::empty) throw std::runtime_error("long_impl value is empty"); return value_; }

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool has_value() const { return value_ != long_impl::empty; }

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        nullable() : value_(long_impl::empty) {}

        /// <summary>
        /// Create from native long.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        nullable(int64_t value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed long.
        /// Null object becomes empty nullable.
        /// </summary>
        explicit nullable(object rhs) { if (!rhs.IsEmpty()) *this = (int64_t) rhs; }

        /// <summary>Copy constructor.</summary>
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.</summary>
        int64_t value_or_default() const { return value_or_default(int64_t()); }

        /// <summary>Retrieves the value of the current nullable<T> object,
        /// or the specified default value.</summary>
        int64_t value_or_default(int64_t default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        explicit operator int64_t() const { return value(); }

        /// <summary>
        /// Assign native long.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        nullable& operator=(int64_t rhs) { value_ = rhs; return *this; }
    };

    /// <summary>
    /// nullable double is initialized to null (empty) by default ctor.
    /// Conversion to double when in null state results in an error.
    ///
    /// This class uses a sentinel to represent null (empty) state,
    /// ensuring no size overhead compared to the native double type.
    /// </summary>
    template <>
    class nullable<double>
    {
        typedef nullable self;

    private:
        double value_ = double_impl::empty;

    public: // PROPERTIES

        typedef double value_type;

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        double value() const { if (value_ == double_impl::empty) throw std::runtime_error("Double value is empty"); return value_; }

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        bool has_value() const { return value_ != double_impl::empty; }

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        nullable() : value_(double_impl::empty) {}

        /// <summary>
        /// Create from native double.
        ///
        /// If sentinel value for null state is passed to this constructor,
        /// no error occurs and the object is constructed in null state.
        /// </summary>
        nullable(double value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed double.
        /// Null object becomes empty nullable.
        /// </summary>
        explicit nullable(object rhs) { if (!rhs.IsEmpty()) *this = (double) rhs; }

        /// <summary>Copy constructor.</summary>
        nullable(const nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current nullable object,
        /// or the default value of the underlying type.</summary>
        double value_or_default() const { return value_or_default(double()); }

        /// <summary>Retrieves the value of the current nullable<T> object,
        /// or the specified default value.</summary>
        double value_or_default(double default_value) const { return has_value() ? value_ : default_value; }

    public: // OPERATORS

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        explicit operator double() const { return value(); }

        /// <summary>
        /// Assign native double.
        ///
        /// If sentinel value for null state is passed to this operator,
        /// no error occurs and the object reverts to null (empty) state.
        /// </summary>
        nullable& operator=(double rhs) { value_ = rhs; return *this; }

        bool operator ==(double rhs) const { return value_ == rhs; }
        bool operator ==(nullable<double> rhs) const { return value_ == rhs.value_or_default(); }

    };
}
