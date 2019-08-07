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
#include <dot/system/object_impl.hpp>

namespace dot
{
    /// Wrapper around int to make it convertible to object (boxing).
    class DOT_CLASS long_impl : public virtual object_impl
    {
        friend object;
        int64_t value_;

    public: // CONSTRUCTORS

        /// Create from value (box).
        long_impl(int64_t value) : value_(value) {}

    public: //  CONSTANTS

        /// Sentinel value representing uninitialized state.
        static constexpr int64_t empty = INT64_MIN;

    public: // STATIC

        /// Converts the string representation of a number to its 64-bit signed integer equivalent.
        static int64_t parse(string s);

    public: // METHODS

        /// Returns a value indicating whether this instance is equal to a specified object.
        bool equals(object obj) override;

        /// Returns the hash code for this instance.
        virtual size_t hash_code() override;

        /// Converts the numeric value of this instance to its equivalent string representation.
        virtual string to_string() override;

        static type_t typeof();
        virtual type_t type() override;
    };

}
