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
#include <dot/system/String.hpp>
#include <dot/system/Environment.hpp>

namespace dot
{
    class StringBuilderImpl; using StringBuilder = ptr<StringBuilderImpl>;

    /// <summary>
    /// Builds a string incrementally.
    /// </summary>
    class StringBuilderImpl final : public virtual ObjectImpl, public std::string
    {
        typedef std::string base;
        friend StringBuilder new_StringBuilder();

    private: // CONSTRUCTORS

        /// <summary>
        /// Initializes an empty instance of the StringBuilder class.
        ///
        /// This constructor is private. Use new_StringBuilder(...)
        /// function with matching signature instead.
        /// </summary>
        StringBuilderImpl() = default;

    public: // METHODS

        /// <summary>A string representing the current type.</summary>
        virtual String ToString() override
        {
            // Returns a copy of the string, not a reference to the same string
            // Further changes to StringBuilder will not affect the previously
            // returned string.
            return new_String(*this);
        }

        /// <summary>
        /// Appends the string returned by processing a composite format string, which contains
        /// zero or more format items, to this instance. Each format item is replaced by the
        /// string representation of a corresponding object argument.
        /// </summary>
        template <typename First, typename ...Args>
        void AppendFormat(const String& format, const First& f, const Args& ...args)
        {
            *this += *String::Format(format, f, args...);
        }

        /// <summary>
        /// Appends the string representation of a specified object to this instance.
        /// </summary>
        template <typename T>
        void Append(const T& arg)
        {
            *this += *String::Format("{0}", arg);
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
        /// Removes all characters from the current StringBuilder instance.
        /// </summary>
        void Clear()
        {
            this->clear();
        }
    };

    /// <summary>
    /// Initializes an empty instance of the StringBuilder class.
    /// </summary>
    inline StringBuilder new_StringBuilder() { return new StringBuilderImpl(); }
}
