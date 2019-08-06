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

#include <dot/precompiled.hpp>
#include <dot/implement.hpp>
#include <dot/noda_time/local_date_util.hpp>
#include <dot/system/exception.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    dot::local_date local_date_util::parse(dot::string value)
    {
        boost::posix_time::time_input_facet* facet = new boost::posix_time::time_input_facet();
        facet->format("%Y-%m-%d");
        std::istringstream stream(*value);
        stream.imbue(std::locale(std::locale::classic(), facet));

        boost::posix_time::ptime ptime;
        stream >> ptime;

        // If default constructed date is passed, error message
        if (ptime == boost::posix_time::not_a_date_time) throw dot::exception(dot::string::format(
            "String representation of default constructed date {0} "
            "passed to local_date.Parse(date) method.", value));

        return ptime.date();
    }

    int local_date_util::to_iso_int(dot::local_date value)
    {
        int result = value.year() * 10'000 + value.month() * 100 + value.day();
        return result;
    }

    dot::local_date local_date_util::parse_iso_int(int value)
    {
        // Extract year, month, day
        int year = value / 100'00;
        value -= year * 100'00;
        int month = value / 100;
        value -= month * 100;
        int day = value;

        // Create local_date object
        return dot::local_date(year, month, day);
    }
}
