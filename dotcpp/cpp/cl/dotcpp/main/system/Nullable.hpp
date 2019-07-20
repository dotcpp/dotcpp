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
#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Bool.hpp>
#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    /// <summary>Represents a value type that can be assigned null.</summary>
    template <class T>
    class Nullable : public std::optional<T>
    {
        typedef Nullable self;
        typedef std::optional<T> base;

    public: // PROPERTIES

        /// <summary>Gets the value of the current Nullable object
        /// if it has been assigned a valid underlying value.</summary>
        DOT_GET(T, Value, { return value(); })

        /// <summary>Gets a value indicating whether the current Nullable
        /// object has a valid value of its underlying type.</summary>
        DOT_GET(bool, HasValue, { return has_value(); })

    public: // CONSTRUCTORS

        /// <summary>Default constructor of Nullable.</summary>
        Nullable() = default;

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

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        T GetValueOrDefault() { return GetValueOrDefault(T()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        T GetValueOrDefault(T defaultValue) { return value_or(defaultValue); }

    public: // OPERATORS

        /// <summary>Defines an explicit conversion of a Nullable
        /// instance to its underlying value.</summary>
        explicit operator T() { return Value; }
    };

    /// <summary>Represents a value type that can be assigned null.</summary>
    template <>
    class Nullable<bool>
    {
        typedef Nullable self;

    private:
        int value_ = Bool::Empty;

    public: // PROPERTIES

        /// <summary>Gets the value of the current Nullable object
        /// if it has been assigned a valid underlying value.</summary>
        DOT_GET(bool, Value, {
            switch (value_)
            {
                case 1: return true;
                case 0: return false;
                case Bool::Empty: throw std::runtime_error("Bool value is empty");
                default: throw std::runtime_error("Unknown internal value in NullableBool.");
            }
        })

        /// <summary>Gets a value indicating whether the current Nullable
        /// object has a valid value of its underlying type.</summary>
        DOT_GET(bool, HasValue, { return value_ != Bool::Empty; })

    public: // CONSTRUCTORS

        /// <summary>Default constructor of Nullable.</summary>
        Nullable() : value_(Bool::Empty) {}

        /// <summary>Initializes a new instance of the Nullable
        /// structure to the specified value.</summary>
        Nullable(bool value) : value_(value ? 1 : 0) {}

        /// <summary>
        /// Supports cast (explicit constructor) from Object.
        ///
        /// Error if Object does is not a boxed T.
        /// Null Object becomes empty Nullable.
        /// </summary>
        explicit Nullable(Object rhs) { if (!rhs.IsEmpty()) *this = (bool) rhs; }

    public: // METHODS

        /// <summary>Retrieves the value of the current Nullable object,
        /// or the default value of the underlying type.</summary>
        bool GetValueOrDefault() { return GetValueOrDefault(bool()); }

        /// <summary>Retrieves the value of the current Nullable<T> object,
        /// or the specified default value.</summary>
        bool GetValueOrDefault(bool defaultValue) { return HasValue ? value_ : defaultValue; }

    public: // OPERATORS

        /// <summary>Defines an explicit conversion of a Nullable
        /// instance to its underlying value.</summary>
        explicit operator bool() { return Value; }
    };
}
