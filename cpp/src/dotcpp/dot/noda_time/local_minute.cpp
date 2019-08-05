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
#include <dot/noda_time/local_minute.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/system/string.hpp>
#include <dot/system/exception.hpp>

namespace dot
{
    local_minute::local_minute(int hour, int minute)
    {
        if (hour < 0 || hour > 23) throw exception(string::format("Hour {0} specified in local_minute constructor is not between 0 and 23.", hour));
        if (minute < 0 || minute > 59) throw exception(string::format("Minute {0} specified in local_minute constructor is not between 0 and 59.", minute));

        hour_ = hour;
        minute_ = minute;
    }

    local_minute::local_minute(const local_minute& other)
    {
        *this = other;
    }

    local_time local_minute::to_local_time() const
    {
        return local_time(hour(), minute());
    }

    int local_minute::compare_to(const local_minute& other) const
    {
        if (minute_of_day() > other.minute_of_day()) return 1;
        if (minute_of_day() < other.minute_of_day()) return -1;
        return 0;
    }

    size_t local_minute::hash_code() const
    {
        return std::hash<int>()(minute_of_day());
    }

    bool local_minute::equals(const local_minute& other) const
    {
        return *this == other;
    }

    string local_minute::to_string() const
    {
        // local_minute is serialized to ISO 8601 string in hh:mm format
        string result = string::format("{0:02}:{1:02}", hour(), minute());
        return result;
    }

    bool local_minute::operator==(const local_minute& other) const
    {
        return minute_of_day() == other.minute_of_day();
    }

    bool local_minute::operator!=(const local_minute& other) const
    {
        return minute_of_day() != other.minute_of_day();
    }

    bool local_minute::operator<(const local_minute& other) const
    {
        return minute_of_day() < other.minute_of_day();
    }

    bool local_minute::operator<=(const local_minute& other) const
    {
        return minute_of_day() <= other.minute_of_day();
    }

    bool local_minute::operator>(const local_minute& other) const
    {
        return minute_of_day() > other.minute_of_day();
    }

    bool local_minute::operator>=(const local_minute& other) const
    {
        return minute_of_day() >= other.minute_of_day();
    }
}
