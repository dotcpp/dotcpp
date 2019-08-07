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
#include <dot/system/environment.hpp>

namespace dot
{
    class string_builder_impl; using string_builder = ptr<string_builder_impl>;

    /// Builds a string incrementally.
    class string_builder_impl final : public virtual object_impl, public std::string
    {
        typedef std::string base;
        friend string_builder make_string_builder();

    private: // CONSTRUCTORS

        /// Initializes an empty instance of the string_builder class.
        ///
        /// This constructor is private. Use make_string_builder(...)
        /// function with matching signature instead.
        string_builder_impl() = default;

    public: // METHODS

        /// A string representing the current type.
        virtual string to_string() override
        {
            // Returns a copy of the string, not a reference to the same string
            // Further changes to string_builder will not affect the previously
            // returned string.
            return make_string(*this);
        }

        /// Appends the string returned by processing a composite format string, which contains
        /// zero or more format items, to this instance. Each format item is replaced by the
        /// string representation of a corresponding object argument.
        template <typename First, typename ...Args>
        void append_format(const string& format, const First& f, const Args& ...args)
        {
            *this += *string::format(format, f, args...);
        }

        /// Appends the string representation of a specified object to this instance.
        template <typename T>
        void append(const T& arg)
        {
            *this += *string::format("{0}", arg);
        }

        /// Appends a copy of a specified string and the default
        /// line terminator, to the end of this instance.
        template <typename ...Args>
        void append_line(const Args& ...args)
        {
            append(args...);
            append_line();
        }

        /// Appends the default line terminator, to the end of this instance.
        void append_line()
        {
            *this += *environment::new_line;
        }

        /// Removes all characters from the current string_builder instance.
        void clear()
        {
            this->clear();
        }
    };

    /// Initializes an empty instance of the string_builder class.
    inline string_builder make_string_builder() { return new string_builder_impl(); }
}
