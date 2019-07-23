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
#include <dot/system/ObjectImpl.hpp>

namespace dot
{
    /// <summary>
    /// Represents a single character of a UTF-8 string.
    ///
    /// It can be represented by a variable number of
    /// bytes and is stored in std::string rather than char. 
    /// </summary>
    class Char : detail::const_string_base
    {
        typedef detail::const_string_base base;

    public: // CONSTRUCTORS

        /// <summary>Create from a single ASCII character.</summary>
        Char(char c) : base(std::to_string(c)) {}
    };

    /// <summary>Wrapper around char to make it convertible to Object (boxing).</summary>
    class CharImpl : public virtual ObjectImpl
    {
        friend Object;
        char value_;

    public: // CONSTRUCTORS

        /// <summary>Create from value (box).</summary>
        CharImpl(char value) : value_(value) {}

    public: // METHODS

        /// <summary>Returns a value indicating whether this instance is equal to a specified object.</summary>
        virtual bool Equals(Object obj) override;

        /// <summary>Returns the hash code for this instance.</summary>
        virtual size_t GetHashCode() override;

        /// <summary>Converts the numeric value of this instance to its equivalent string representation.</summary>
        virtual String ToString() override;

        static Type typeof();
        virtual Type GetType() override;
    };
}
