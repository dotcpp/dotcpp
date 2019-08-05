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
#include <dot/system/object.hpp>
#include <dot/detail/struct_wrapper.hpp>
#include <dot/noda_time/local_date_time.hpp>
#include <dot/noda_time/period.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/local_date.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    /// <summary>
    /// In C\# local datetime is a struct, and as all structs has default constructor
    /// that initializes all backing variables to 0. This means that default
    /// constructed value corresponds to 0001-01-01 00:00:00. Because Boost date_time
    /// library does not accept the date 0001-01-01, we will instead use the Unix epoch
    /// 1970-01-01 as default constructed value.
    /// </summary>
    local_date_time::local_date_time()
        : ptime(local_date{ 1970, 1, 1 }, { 0, 0, 0 })
    {
    }

    /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
    local_date_time::local_date_time(int year, int month, int day, int hour, int minute)
        : ptime(local_date {year, month, day}, {hour, minute, 0})
    {}

    /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
    local_date_time::local_date_time(int year, int month, int day, int hour, int minute, int second)
        : ptime(local_date {year, month, day}, {hour, minute, second})
    {}

    /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
    local_date_time::local_date_time(int year, int month, int day, int hour, int minute, int second, int millisecond)
        : ptime(local_date {year, month, day}, {hour, minute, second, millisecond * 1000})
    {}

    /// <summary>Create from Boost posix_time.</summary>
    local_date_time::local_date_time(const ptime& time)
        : ptime(time)
    {}

    local_date_time::local_date_time(const local_date_time& other)
    {
        *this = other;
    }

    local_date_time::local_date_time(const local_date& date, const local_time& time) :
        ptime(date, time)
    {}

    local_date_time::local_date_time(object const& rhs) { *this = rhs.operator local_date_time(); }

    local_date_time local_date_time::Add(const local_date_time& local_date_time, const period& period)
    {
        return local_date_time + period;
    }

    int local_date_time::compare_to(const local_date_time& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool local_date_time::equals(const local_date_time& other) const
    {
        return *this == other;
    }

    string local_date_time::to_string() const
    {
        boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
        facet->format("%Y-%m-%d %H:%M:%S.%f");
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), facet));
        stream << *this;
        return stream.str().substr(0, 23);
    }

    period local_date_time::Minus(const local_date_time& local_date_time) const
    {
        return *this - local_date_time;
    }

    local_date_time local_date_time::Minus(const period& period) const
    {
        return *this - period;
    }

    local_date_time local_date_time::Next(int targetDayOfWeek) const
    {
        return {local_date(date()).next(targetDayOfWeek), time_of_day()};
    }

    local_date_time local_date_time::Plus(const period& period) const
    {
        return *this + period;
    }

    local_date_time local_date_time::PlusDays(int days) const
    {
        return *this + boost::gregorian::days(days);
    }

    local_date_time local_date_time::PlusHours(int64_t hours) const
    {
        return *this + boost::posix_time::hours(hours);
    }

    local_date_time local_date_time::PlusMilliseconds(int64_t milliseconds) const
    {
        return *this + boost::posix_time::milliseconds(milliseconds);
    }

    local_date_time local_date_time::PlusMinutes(int64_t minutes) const
    {
        return *this + boost::posix_time::minutes(minutes);
    }

    local_date_time local_date_time::PlusMonths(int months) const
    {
        return *this + boost::gregorian::months(months);
    }

    local_date_time local_date_time::PlusSeconds(int64_t seconds) const
    {
        return *this + boost::posix_time::seconds(seconds);
    }

    local_date_time local_date_time::PlusWeeks(int weeks) const
    {
        return *this + boost::gregorian::weeks(weeks);
    }

    local_date_time local_date_time::PlusYears(int years) const
    {
        return *this + boost::gregorian::years(years);
    }

    local_date_time local_date_time::Previous(int targetDayOfWeek) const
    {
        return {local_date(date()).previous(targetDayOfWeek), time_of_day()};
    }

    period local_date_time::Subtract(const local_date_time& lhs, const local_date_time& rhs)
    {
        return lhs - rhs;
    }

    local_date_time local_date_time::Subtract(const local_date_time& local_date_time, const period& period)
    {
        return local_date_time - period;
    }

    local_date_time local_date_time::operator+(const period& period) const
    {
        return static_cast<ptime>(*this) + static_cast<time_duration>(period);
    }

    bool local_date_time::operator==(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) == static_cast<ptime>(other);
    }

    bool local_date_time::operator!=(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) != static_cast<ptime>(other);
    }

    bool local_date_time::operator>(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) > static_cast<ptime>(other);
    }

    bool local_date_time::operator>=(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) >= static_cast<ptime>(other);
    }

    bool local_date_time::operator<(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) < static_cast<ptime>(other);
    }

    bool local_date_time::operator<=(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) <= static_cast<ptime>(other);
    }

    period local_date_time::operator-(const local_date_time& other) const
    {
        return static_cast<ptime>(*this) - static_cast<ptime>(other);
    }

    local_date_time local_date_time::operator-(const period& period) const
    {
        return static_cast<ptime>(*this) - static_cast<time_duration>(period);
    }
}
