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
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/period.hpp>
#include <dot/noda_time/local_date_time.hpp>
#include <dot/system/string.hpp>
#include <dot/system/object.hpp>

namespace dot
{
    /// 
    /// Because in C\# local_date_time is a struct, it has default constructor
    /// that initializes all backing variables to 0. This means that default
    /// constructed value corresponds to 0001-01-01 00:00:00. We will
    /// replicate this behavior here.
    /// 
    local_time::local_time()
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration{ 0, 0, 0 })
    {}

    /// Creates a local time at the given hour and minute, with second, millisecond-of-second and tick-of-millisecond values of zero.
    local_time::local_time(int hour, int minute)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, 0})
    {}

    /// Creates a local time at the given hour, minute and second, with millisecond-of-second and tick-of-millisecond values of zero.
    local_time::local_time(int hour, int minute, int second)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second})
    {}

    /// Creates a local time at the given hour, minute, second and millisecond, with a tick-of-millisecond value of zero.
    local_time::local_time(int hour, int minute, int second, int millisecond)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second, millisecond * 1000})
    {}

    /// Create from Boost time_duration.
    local_time::local_time(const time_duration& time)
        : ptime(boost::gregorian::date(1970, 1, 1), time)
    {}

    /// Create from Boost posix_time.
    local_time::local_time(const ptime& time)
        : ptime(time)
    {}

    local_time::local_time(object const& rhs) { *this = rhs.operator local_time(); }

    local_time::local_time(const local_time& other)
    {
        *this = other;
    }

    local_time local_time::Add(const local_time& time, const period& period)
    {
        return time + period;
    }

    int local_time::compare_to(const local_time& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool local_time::equals(const local_time& other) const
    {
        return *this == other;
    }

    string local_time::to_string() const
    {
        boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
        facet->format("%H:%M:%S.%f");
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), facet));
        stream << *this;
        return stream.str().substr(0, 12);
    }

    period local_time::Minus(const local_time& time) const
    {
        return *this - time;
    }

    local_time local_time::Minus(const period& period) const
    {
        return *this - period;
    }

    local_date_time local_time::On(const local_date& date)
    {
        return {date, *this};
    }

    local_time local_time::Plus(const period& period) const
    {
        return *this + period;
    }

    local_time local_time::PlusHours(int64_t hours) const
    {
        return *this + boost::posix_time::hours(hours);
    }

    local_time local_time::PlusMilliseconds(int64_t milliseconds) const
    {
        return *this + boost::posix_time::milliseconds(milliseconds);
    }

    local_time local_time::PlusMinutes(int64_t minutes) const
    {
        return *this + boost::posix_time::minutes(minutes);
    }

    local_time local_time::PlusSeconds(int64_t seconds) const
    {
        return *this + boost::posix_time::seconds(seconds);
    }

    period local_time::Subtract(const local_time& lhs, const local_time& rhs)
    {
        return lhs - rhs;
    }

    local_time local_time::Subtract(const local_time& time, const period& period)
    {
        return time - period;
    }

    local_time local_time::operator+(const period& period) const
    {
        return static_cast<ptime>(*this) + static_cast<time_duration>(period);
    }

    bool local_time::operator==(const local_time& other) const
    {
        return time_of_day() == other.time_of_day();
    }

    bool local_time::operator!=(const local_time& other) const
    {
        return time_of_day() != other.time_of_day();
    }

    bool local_time::operator>(const local_time& other) const
    {
        return time_of_day() > other.time_of_day();
    }

    bool local_time::operator>=(const local_time& other) const
    {
        return time_of_day() >= other.time_of_day();
    }

    bool local_time::operator<(const local_time& other) const
    {
        return time_of_day() < other.time_of_day();
    }

    bool local_time::operator<=(const local_time& other) const
    {
        return time_of_day() <= other.time_of_day();
    }

    period local_time::operator-(const local_time& other) const
    {
        return static_cast<ptime>(*this) - static_cast<ptime>(other);
    }

    local_time local_time::operator-(const period& period) const
    {
        return static_cast<ptime>(*this) - static_cast<time_duration>(period);
    }

    local_time::operator time_duration() const
    {
        return time_of_day();
    }
}
