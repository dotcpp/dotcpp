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
#include <fmt/core.h>
#include <dot/system/string.hpp>
#include <dot/system/Environment.hpp>

namespace dot
{
    class string_builder_impl; using string_builder = ptr<string_builder_impl>;

    /// <summary>
    /// Builds a string incrementally.
    /// </summary>
    class string_builder_impl final : public virtual object_impl, public std::string
    {
        typedef std::string base;
        friend string_builder make_string_builder();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes an empty instance of the string_builder class.
        ///
        /// This constructor is private. Use make_string_builder(...)
        /// function with matching signature instead.
        /// </summary>
        string_builder_impl() = default;

    public: // METHODS

        /// <summary>A string representing the current type.</summary>
        virtual string to_string() override
        {
            // Returns a copy of the string, not a reference to the same string
            // Further changes to string_builder will not affect the previously
            // returned string.
            return make_string(*this);
        }

        /// <summary>
        /// Appends the string returned by processing a composite format string, which contains
        /// zero or more format items, to this instance. Each format item is replaced by the
        /// string representation of a corresponding object argument.
        /// </summary>
        template <typename First, typename ...Args>
        void AppendFormat(const string& format, const First& f, const Args& ...args)
        {
            *this += *string::format(format, f, args...);
        }

        /// <summary>
        /// Appends the string representation of a specified object to this instance.
        /// </summary>
        template <typename T>
        void Append(const T& arg)
        {
            *this += *string::format("{0}", arg);
        }

        /// <summary>
        /// Appends a copy of a specified string and the default
        /// line terminator, to the end of this instance.
        /// </summary>
        template <typename ...Args>
        void AppendLine(const Args& ...args)
        {
            Append(args...);
            AppendLine();
        }

        /// <summary>
        /// Appends the default line terminator, to the end of this instance.
        /// </summary>
        void AppendLine()
        {
            *this += *Environment::NewLine;
        }

        /// <summary>
        /// Removes all characters from the current string_builder instance.
        /// </summary>
        void Clear()
        {
            this->clear();
        }
    };

    /// <summary>
    /// Initializes an empty instance of the string_builder class.
    /// </summary>
    inline string_builder make_string_builder() { return new string_builder_impl(); }
}
