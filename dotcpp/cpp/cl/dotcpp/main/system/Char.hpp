/*
Copyright (C) 2003-present CompatibL

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

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/detail/const_string.hpp>

namespace cl
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
}
