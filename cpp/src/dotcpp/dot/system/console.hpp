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

namespace dot
{
    /// Represents the standard input, output, and
    /// error streams for console applications.
    class DOT_CLASS console final
    {
    private: // CONSTRUCTORS

        console() = delete;
        console(const console&) = delete;
        console& operator=(const console&) = delete;

    public: // STATIC

        /// Writes the text representation of the argument array of objects 
        /// to the standard output stream using the specified format information.
        template <typename First, typename ...Args>
        static void write(const string& format, const First& f, const Args& ...args)
        {
            std::cout << *string::format(format, f, args...);
        }

        /// Writes the text representation of the specified object 
        /// to the standard output stream.
        template <typename T>
        static void write(const T& arg)
        {
            std::cout << *string::format("{0}", arg);
        }

        /// Writes the text representation of the specified array of objects,
        /// followed by the current line terminator, to the standard output
        /// stream using the specified format information.
        template <typename ...Args>
        static void write_line(const Args& ...args)
        {
            write(args...);
            std::cout << std::endl;
        }
    };
}
