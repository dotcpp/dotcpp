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
#include <dot/system/collections/generic/dictionary.hpp>

namespace dot
{
    /// <summary>
    /// enum_base wrapper for use in data structures.
    /// Provides the base class for enumerations.
    /// </summary>
    class DOT_CLASS enum_base
    {
        typedef enum_base self;

    public:
        typedef self element_type;

    protected: // FIELDS

        int value_ = 0;

    public: // CONSTRUCTORS

        /// <summary>Default constructor.</summary>
        enum_base() = default;

        /// <summary>Create from int.</summary>
        enum_base(int value) : value_(value) {}

        /// <summary>Copy constructor.</summary>
        enum_base(const enum_base& rhs) : value_(rhs.value_) {}

        /// <summary>Constructor from object.</summary>
        enum_base(object rhs)
        {
            value_ = dynamic_cast<enum_base&>(*rhs).value_;
        }

    public: // METHODS

        /// <summary>Converts the value of this instance to its equivalent string representation.</summary>
        string to_string();

        /// <summary>Returns the hash code for the value of this instance.</summary>
        size_t hash_code();

        /// <summary>Returns a value indicating whether this instance is equal to a specified object.</summary>
        bool equals(object obj);

    public: // STATIC

        /// <summary>
        /// Converts the string representation of the name or numeric value of
        /// one or more enumerated constants to an equivalent enumerated object.
        /// </summary>
        static object parse(type_t enumType, string value);

    protected: // PROTECTED

        virtual dictionary<string, int> get_enum_map() = 0;

    public: // OPERATORS

        /// <summary>Convert to int.</summary>
        operator int() const { return value_; }

        /// <summary>Assign int to enum_base.</summary>
        enum_base& operator=(int rhs) { value_ = rhs; return *this; }

        /// <summary>Copy assign.</summary>
        enum_base& operator=(const enum_base& rhs) { value_ = rhs.value_; return *this; }

    public:

        DOT_TYPE_BEGIN("System", "Enum")
            ->is_enum()
        DOT_TYPE_END()
    };
}

