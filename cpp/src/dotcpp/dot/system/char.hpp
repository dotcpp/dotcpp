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
#include <dot/detail/const_string_base.hpp>
#include <dot/system/object_impl.hpp>

namespace dot
{
    /// Represents a single character of a UTF-8 string.
    ///
    /// It can be represented by a variable number of
    /// bytes and is stored in std::string rather than char. 
    class Char : detail::const_string_base
    {
        typedef detail::const_string_base base;

    public: // CONSTRUCTORS

        /// Create from a single ASCII character.
        Char(char c) : base(std::to_string(c)) {}
    };

    /// Wrapper around char to make it convertible to object (boxing).
    class char_impl : public virtual object_impl
    {
        friend object;
        char value_;

    public: // CONSTRUCTORS

        /// Create from value (box).
        char_impl(char value) : value_(value) {}

    public: // METHODS

        /// Returns a value indicating whether this instance is equal to a specified object.
        bool equals(object obj) override;

        /// Returns the hash code for this instance.
        virtual size_t hash_code() override;

        /// Converts the numeric value of this instance to its equivalent string representation.
        virtual string to_string() override;

        static type typeof();
        type get_type() override;
    };
}
