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

#include <dot/implement.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/Period.hpp>
#include <dot/noda_time/LocalDateTime.hpp>
#include <dot/system/String.hpp>
#include <dot/system/object.hpp>

namespace dot
{
    /// <summary>
    /// Because in C\# LocalDateTime is a struct, it has default constructor
    /// that initializes all backing variables to 0. This means that default
    /// constructed value corresponds to 0001-01-01 00:00:00. We will
    /// replicate this behavior here.
    /// </summary>
    LocalTime::LocalTime()
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration{ 0, 0, 0 })
    {}

    /// <summary>Creates a local time at the given hour and minute, with second, millisecond-of-second and tick-of-millisecond values of zero.</summary>
    LocalTime::LocalTime(int hour, int minute)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, 0})
    {}

    /// <summary>Creates a local time at the given hour, minute and second, with millisecond-of-second and tick-of-millisecond values of zero.</summary>
    LocalTime::LocalTime(int hour, int minute, int second)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second})
    {}

    /// <summary>Creates a local time at the given hour, minute, second and millisecond, with a tick-of-millisecond value of zero.</summary>
    LocalTime::LocalTime(int hour, int minute, int second, int millisecond)
        : ptime(boost::gregorian::date(1970, 1, 1), time_duration {hour, minute, second, millisecond * 1000})
    {}

    /// <summary>Create from Boost time_duration.</summary>
    LocalTime::LocalTime(const time_duration& time)
        : ptime(boost::gregorian::date(1970, 1, 1), time)
    {}

    /// <summary>Create from Boost posix_time.</summary>
    LocalTime::LocalTime(const ptime& time)
        : ptime(time)
    {}

    LocalTime::LocalTime(object const& rhs) { *this = rhs.operator LocalTime(); }

    LocalTime::LocalTime(const LocalTime& other)
    {
        *this = other;
    }

    LocalTime LocalTime::Add(const LocalTime& time, const Period& period)
    {
        return time + period;
    }

    int LocalTime::CompareTo(const LocalTime& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool LocalTime::Equals(const LocalTime& other) const
    {
        return *this == other;
    }

    String LocalTime::ToString() const
    {
        boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
        facet->format("%H:%M:%S.%f");
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), facet));
        stream << *this;
        return stream.str().substr(0, 12);
    }

    Period LocalTime::Minus(const LocalTime& time) const
    {
        return *this - time;
    }

    LocalTime LocalTime::Minus(const Period& period) const
    {
        return *this - period;
    }

    LocalDateTime LocalTime::On(const LocalDate& date)
    {
        return {date, *this};
    }

    LocalTime LocalTime::Plus(const Period& period) const
    {
        return *this + period;
    }

    LocalTime LocalTime::PlusHours(int64_t hours) const
    {
        return *this + boost::posix_time::hours(hours);
    }

    LocalTime LocalTime::PlusMilliseconds(int64_t milliseconds) const
    {
        return *this + boost::posix_time::milliseconds(milliseconds);
    }

    LocalTime LocalTime::PlusMinutes(int64_t minutes) const
    {
        return *this + boost::posix_time::minutes(minutes);
    }

    LocalTime LocalTime::PlusSeconds(int64_t seconds) const
    {
        return *this + boost::posix_time::seconds(seconds);
    }

    Period LocalTime::Subtract(const LocalTime& lhs, const LocalTime& rhs)
    {
        return lhs - rhs;
    }

    LocalTime LocalTime::Subtract(const LocalTime& time, const Period& period)
    {
        return time - period;
    }

    LocalTime LocalTime::operator+(const Period& period) const
    {
        return static_cast<ptime>(*this) + static_cast<time_duration>(period);
    }

    bool LocalTime::operator==(const LocalTime& other) const
    {
        return time_of_day() == other.time_of_day();
    }

    bool LocalTime::operator!=(const LocalTime& other) const
    {
        return time_of_day() != other.time_of_day();
    }

    bool LocalTime::operator>(const LocalTime& other) const
    {
        return time_of_day() > other.time_of_day();
    }

    bool LocalTime::operator>=(const LocalTime& other) const
    {
        return time_of_day() >= other.time_of_day();
    }

    bool LocalTime::operator<(const LocalTime& other) const
    {
        return time_of_day() < other.time_of_day();
    }

    bool LocalTime::operator<=(const LocalTime& other) const
    {
        return time_of_day() <= other.time_of_day();
    }

    Period LocalTime::operator-(const LocalTime& other) const
    {
        return static_cast<ptime>(*this) - static_cast<ptime>(other);
    }

    LocalTime LocalTime::operator-(const Period& period) const
    {
        return static_cast<ptime>(*this) - static_cast<time_duration>(period);
    }

    LocalTime::operator time_duration() const
    {
        return time_of_day();
    }
}
