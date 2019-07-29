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
    /// <summary>
    /// Represents the standard input, output, and
    /// error streams for console applications.
    /// </summary>
    class DOT_CLASS Console final
    {
    private: // CONSTRUCTORS

        Console() = delete;
        Console(const Console&) = delete;
        Console& operator=(const Console&) = delete;

    public: // STATIC

        /// <summary>
        /// Writes the text representation of the argument array of objects 
        /// to the standard output stream using the specified format information.
        /// </summary>
        template <typename First, typename ...Args>
        static void Write(const string& format, const First& f, const Args& ...args)
        {
            std::cout << *string::Format(format, f, args...);
        }

        /// <summary>
        /// Writes the text representation of the specified object 
        /// to the standard output stream.
        /// </summary>
        template <typename T>
        static void Write(const T& arg)
        {
            std::cout << *string::Format("{0}", arg);
        }

        /// <summary>
        /// Writes the text representation of the specified array of objects,
        /// followed by the current line terminator, to the standard output
        /// stream using the specified format information.
        /// </summary>
        template <typename ...Args>
        static void WriteLine(const Args& ...args)
        {
            Write(args...);
            std::cout << std::endl;
        }
    };
}
