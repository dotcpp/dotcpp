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
#include <dot/system/objectimpl.hpp>

namespace dot
{
    /// <summary>Wrapper around double to make it convertible to object (boxing).</summary>
    class DoubleImpl : public virtual object_impl
    {
        friend object;
        double value_;

    public: // CONSTRUCTORS

        /// <summary>Create from value (box).</summary>
        DoubleImpl(double value) : value_(value) {}

    public: // METHODS

        /// <summary>Returns a value indicating whether this instance is equal to a specified object.</summary>
        virtual bool Equals(object obj) override;

        /// <summary>Returns the hash code for this instance.</summary>
        virtual size_t GetHashCode() override;

        /// <summary>Converts the numeric value of this instance to its equivalent string representation.</summary>
        virtual string to_string() override;

    public: // REFLECTION

        static Type typeof();
        virtual Type GetType() override;
    };

    /// <summary>
    /// Provides constants and static methods for double type.
    /// </summary>
    class DOT_CLASS Double
    {
    public: //  CONSTANTS

        /// <summary>Sentinel value representing uninitialized state.</summary>
        static constexpr double Empty = -1e100;

        /// <summary>Tolerance used in comparison.</summary>
        static constexpr double Tolerance = 1e-10;

    public: // STATIC

        /// <summary>Converts the string representation of a number to its double-precision floating-point number equivalent.</summary>
        static double Parse(string s);
    };
}

