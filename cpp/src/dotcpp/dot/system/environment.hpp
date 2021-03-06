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
    /// Provides information about, and means to manipulate, the current environment and platform.
    class DOT_CLASS environment final
    {
    private: // CONSTRUCTORS

        environment() = delete;
        environment(const environment&) = delete;
        environment& operator=(const environment&) = delete;

    public: // STATIC

        /// Gets the newline string defined for this environment.
        static string make_line;
    };
}
