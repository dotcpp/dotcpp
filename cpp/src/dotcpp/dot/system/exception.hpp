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

namespace dot
{
    class string;
    class string_impl;

    /// Represents errors that occur during application execution.
    class DOT_CLASS exception : public std::runtime_error
    {
        typedef std::runtime_error base;

    public: // CONSTRUCTORS

        /// Create with default message.
        exception();

        /// Create with a specified error message.
        exception(const std::string& msg);

        /// Create with a specified error message.
        exception(const char* msg);

        /// Create with a specified error message.
        exception(string msg);

    public: // METHODS

        /// Message that describes the current exception.
        virtual string message() const;
    };


}
