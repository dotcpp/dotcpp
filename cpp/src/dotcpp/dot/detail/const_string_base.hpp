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
    namespace detail
    {
        /// 
        /// This class is used as base class of string_impl.
        ///
        /// The objective is to make it possible to pass this class to functions
        /// accepting  std::string. Because C# string is immutable, const_string_base
        /// derives from std::string and then hides all non-const methods.
        /// 
        class const_string_base : public std::string
        {
            typedef std::string base;

        public:

            /// Create empty string.
            const_string_base() = default;

            /// Create from std::string or string literal.
            const_string_base(const std::string& value) : base(value) {}

            /// Create from const char*, null pointer is converted to to empty value.
            const_string_base(const char* value) : base(value) {}

            // TODO - delete non-const methods of std::string
        };
    }
}
