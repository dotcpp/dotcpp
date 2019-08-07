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
#include <dot/noda_time/local_date_time.hpp>
#include <chrono>

namespace dot
{
    class DOT_CLASS local_date_time_util
    {
    public: // STATIC

        /// Parse string using standard ISO 8601 date pattern yyyy-mm-ddThh:mm::ss.fff, throw if invalid format.
        /// No variations from the standard format are accepted and no delimiters can be changed or omitted.
        /// Specifically, ISO int-like string using yyyymmddhhmmssfff format without delimiters is not accepted.
        static dot::local_date_time parse(dot::string value);

        /// Convert local_date_time to ISO 8601 8 digit long in yyyymmddhhmmssfff format.
        static int64_t to_iso_long(dot::local_date_time value);

        /// Parse ISO 8601 17 digit long in yyyymmddhhmmssfff format, throw if invalid format.
        static dot::local_date_time parse_iso_long(int64_t value);

        /// Convert local_date_time to std::chrono::milliseconds.
        static std::chrono::milliseconds to_std_chrono(dot::local_date_time value);

        /// Convert std::chrono::milliseconds to local_date_time.
        static dot::local_date_time from_std_chrono(std::chrono::milliseconds value);
    };
}
