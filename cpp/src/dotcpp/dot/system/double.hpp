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
    /// Wrapper around double to make it convertible to object (boxing).
    class DOT_CLASS double_impl : public virtual object_impl
    {
        friend object;
        double value_;

    public: // CONSTRUCTORS

        /// Create from value (box).
        double_impl(double value) : value_(value) {}

    public: //  CONSTANTS

        /// Sentinel value representing uninitialized state.
        static constexpr double empty = -1e100;

        /// Tolerance used in comparison.
        static constexpr double tolerance = 1e-10;

    public: // STATIC

        /// Converts the string representation of a number to its double-precision floating-point number equivalent.
        static double parse(string s);

    public: // METHODS

        /// Returns a value indicating whether this instance is equal to a specified object.
        bool equals(object obj) override;

        /// Returns the hash code for this instance.
        virtual size_t hash_code() override;

        /// Converts the numeric value of this instance to its equivalent string representation.
        virtual string to_string() override;

    public: // REFLECTION

        static type_t typeof();
        type_t get_type() override;
    };

}

