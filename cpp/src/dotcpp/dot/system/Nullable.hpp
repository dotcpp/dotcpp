/*
Copyright (C) 2003-present CompatibL

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
#include <dot/system/Object.hpp>

namespace dot
{
    /// <summary>Represents a value type that can be assigned null.</summary>
    template <class T>
    class Nullable : public std::optional<T>
    {
        typedef Nullable self;
        typedef std::optional<T> base;

    public: // PROPERTIES

        typedef T value_type;

        /// <summary>Gets the value of the current Nullable object
        /// if it has been assigned a valid underlying value.</summary>
        DOT_GET(T, Value, { return this->value(); })

        /// <summary>Gets a value indicating whether the current Nullable
        /// object has a valid value of its underlying type.</summary>
        DOT_GET(bool, HasValue, { return this->has_value(); })

    public: // CONSTRUCTORS

        /// <summary>Default constructor of Nullable.</summary>
        Nullable() = default;

        /// <summary>Construct Nullable from nullptr.</summary>
        Nullable(nullptr_t) {}

        /// <summary>Initializes a new instance of the Nullable
        /// structure to the specified value.</summary>
        Nullable(T value) : base(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed T.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (T) rhs; }

        /// <summary>Copy constructor.</summary>
        Nullable(const Nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        T GetValueOrDefault() const { return GetValueOrDefault(T()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        T GetValueOrDefault(T defaultValue) const { return value_or(defaultValue); }

    public: // OPERATORS

        /// <summary>Defines an explicit conversion of a Nullable
        /// instance to its underlying value.</summary>
        explicit operator T() const { return Value; }

        Nullable& operator=(nullptr_t) { this->reset(); return *this; }

        bool operator==(nullptr_t) { return !this->HasValue; }
        bool operator!=(nullptr_t) { return this->HasValue; }

        bool operator ==(T rhs) { return GetValueOrDefault() == rhs; }
        bool operator ==(Nullable<T> rhs) { return GetValueOrDefault() == rhs.GetValueOrDefault(); }
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
    class Nullable<bool>
    {
        typedef Nullable self;

    private:
        int value_ = Bool::Empty;

    public: // PROPERTIES

        typedef bool value_type;

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
        DOT_GET(bool, Value, {
            switch (value_)
            {
                case 1: return true;
                case 0: return false;
                case Bool::Empty: throw std::runtime_error("Bool value is empty");
                default: throw std::runtime_error("Unknown internal value in Nullable<bool>.");
            }
        })

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        DOT_GET(bool, HasValue, { return value_ != Bool::Empty; })

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        Nullable() : value_(Bool::Empty) {}

        /// <summary>Create from native bool.</summary>
        Nullable(bool value) : value_(value ? 1 : 0) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed boolean.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (bool) rhs; }

        /// <summary>Copy constructor.</summary>
        Nullable(const Nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        bool GetValueOrDefault() const { return GetValueOrDefault(bool()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        bool GetValueOrDefault(bool defaultValue) const { return HasValue ? value_ : defaultValue; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Bool::Empty; }

    public: // OPERATORS

        /// <summary>Convert to native bool, error if the object is in uninitialized (empty) state.</summary>
        explicit operator bool() const { return Value; }

        /// <summary>Assign native bool.</summary>
        Nullable& operator=(bool rhs) { value_ = rhs ? 1 : 0; return *this; }
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
    class Nullable<int>
    {
        typedef Nullable self;

    private:
        int value_ = Int::Empty;

    public: // PROPERTIES

        typedef int value_type;

        /// <summary>Convert to native double, error if the object is in uninitialized (empty) state.</summary>
        DOT_GET(int, Value, { if (value_ == Int::Empty) throw std::runtime_error("Int value is empty"); return value_; })

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        DOT_GET(bool, HasValue, { return value_ != Int::Empty; })

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        Nullable() : value_(Int::Empty) {}

        /// <summary>
        /// Create from native int.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        Nullable(int value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed int.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (int) rhs; }

        /// <summary>Copy constructor.</summary>
        Nullable(const Nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        int GetValueOrDefault() const { return GetValueOrDefault(int()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        int GetValueOrDefault(int defaultValue) const { return HasValue ? value_ : defaultValue; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Int::Empty; }

    public: // OPERATORS

        /// <summary>Convert to native int, error if the object is in uninitialized (empty) state.</summary>
        explicit operator int() const { return Value; }

        /// <summary>
        /// Assign native int.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        Nullable& operator=(int rhs) { value_ = rhs; return *this; }
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
    class Nullable<int64_t>
    {
        typedef Nullable self;

    private:
        int64_t value_ = Long::Empty;

    public: // PROPERTIES

        typedef int64_t value_type;

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        DOT_GET(int64_t, Value, { if (value_ == Long::Empty) throw std::runtime_error("Long value is empty"); return value_; })

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        DOT_GET(bool, HasValue, { return value_ != Long::Empty; })

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        Nullable() : value_(Long::Empty) {}

        /// <summary>
        /// Create from native long.
        ///
        /// If sentinel value for uninitialized state is passed to this constructor,
        /// no error occurs and the object is constructed in uninitialized state.
        /// </summary>
        Nullable(int64_t value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed long.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (int64_t) rhs; }

        /// <summary>Copy constructor.</summary>
        Nullable(const Nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        int64_t GetValueOrDefault() const { return GetValueOrDefault(int64_t()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        int64_t GetValueOrDefault(int64_t defaultValue) const { return HasValue ? value_ : defaultValue; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Long::Empty; }

    public: // OPERATORS

        /// <summary>Convert to native long, error if the object is in uninitialized (empty) state.</summary>
        explicit operator int64_t() const { return Value; }

        /// <summary>
        /// Assign native long.
        ///
        /// If sentinel value for uninitialized state is passed to this operator,
        /// no error occurs and the object reverts to uninitialized (empty) state.
        /// </summary>
        Nullable& operator=(int64_t rhs) { value_ = rhs; return *this; }
    };

    /// <summary>
    /// Nullable double is initialized to null (empty) by default ctor.
    /// Conversion to double when in null state results in an error.
    ///
    /// This class uses a sentinel to represent null (empty) state,
    /// ensuring no size overhead compared to the native double type.
    /// </summary>
    template <>
    class Nullable<double>
    {
        typedef Nullable self;

    private:
        double value_ = Double::Empty;

    public: // PROPERTIES

        typedef double value_type;

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        DOT_GET(double, Value, { if (value_ == Double::Empty) throw std::runtime_error("Double value is empty"); return value_; })

        /// <summary>Returns true if the object is in uninitialized (empty) state.</summary>
        DOT_GET(bool, HasValue, { return value_ != Double::Empty; })

    public: // CONSTRUCTORS

        /// <summary>Creates in uninitialized (empty) state.</summary>
        Nullable() : value_(Double::Empty) {}

        /// <summary>
        /// Create from native double.
        ///
        /// If sentinel value for null state is passed to this constructor,
        /// no error occurs and the object is constructed in null state.
        /// </summary>
        Nullable(double value) : value_(value) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed double.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (double) rhs; }

        /// <summary>Copy constructor.</summary>
        Nullable(const Nullable& other) { *this = other; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        double GetValueOrDefault() const { return GetValueOrDefault(double()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        double GetValueOrDefault(double defaultValue) const { return HasValue ? value_ : defaultValue; }

        /// <summary>Clear the value and revert to uninitialized (empty) state.</summary>
        void Clear() { value_ = Double::Empty; }

    public: // OPERATORS

        /// <summary>Convert to native double, error if the object is in null (empty) state.</summary>
        explicit operator double() const { return Value; }

        /// <summary>
        /// Assign native double.
        ///
        /// If sentinel value for null state is passed to this operator,
        /// no error occurs and the object reverts to null (empty) state.
        /// </summary>
        Nullable& operator=(double rhs) { value_ = rhs; return *this; }

        bool operator ==(double rhs) const { return value_ == rhs; }
        bool operator ==(Nullable<double> rhs) const { return value_ == rhs.GetValueOrDefault(); }

    };
}
