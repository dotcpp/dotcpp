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

#include <dot/declare.hpp>
#include <dot/detail/enum_macro.hpp>
#include <dot/system/type.hpp>
#include <dot/system/collections/generic/Dictionary.hpp>

namespace dot
{
    /// <summary>
    /// Enum wrapper for use in data structures.
    /// Provides the base class for enumerations.
    /// </summary>
    class DOT_CLASS Enum
    {
        typedef Enum self;

    public:
        typedef self element_type;

    protected: // FIELDS

        int value_ = 0;

    public: // CONSTRUCTORS

        /// <summary>Default constructor.</summary>
        Enum() = default;

        /// <summary>Create from int.</summary>
        Enum(int value) : value_(value) {}

        /// <summary>Copy constructor.</summary>
        Enum(const Enum& rhs) : value_(rhs.value_) {}

        /// <summary>Constructor from object.</summary>
        Enum(object rhs)
        {
            value_ = dynamic_cast<Enum&>(*rhs).value_;
        }

    public: // METHODS

        /// <summary>Converts the value of this instance to its equivalent string representation.</summary>
        string to_string();

        /// <summary>Returns the hash code for the value of this instance.</summary>
        size_t GetHashCode();

        /// <summary>Returns a value indicating whether this instance is equal to a specified object.</summary>
        bool Equals(object obj);

    public: // STATIC

        /// <summary>
        /// Converts the string representation of the name or numeric value of
        /// one or more enumerated constants to an equivalent enumerated object.
        /// </summary>
        static object Parse(type_t enumType, string value);

    protected: // PROTECTED

        virtual Dictionary<string, int> GetEnumMap() = 0;

    public: // OPERATORS

        /// <summary>Convert to int.</summary>
        operator int() const { return value_; }

        /// <summary>Assign int to Enum.</summary>
        Enum& operator=(int rhs) { value_ = rhs; return *this; }

        /// <summary>Copy assign.</summary>
        Enum& operator=(const Enum& rhs) { value_ = rhs.value_; return *this; }

    public:

        DOT_TYPE_BEGIN("System", "Enum")
            ->IsEnum()
        DOT_TYPE_END()
    };
}

