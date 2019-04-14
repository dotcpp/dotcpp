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

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/LocalDateTime.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/Period.hpp>
#include <cl/dotcpp/main/system/LocalTime.hpp>
#include <cl/dotcpp/main/system/LocalDate.hpp>

namespace cl
{
    /// <summary>Initializes to default value that the code will treat as empty.</summary>
    LocalDateTime::LocalDateTime()
    {
    }

    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute)
        : ptime(LocalDate {year, month, day}, {hour, minute, 0})
    {}

    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute, int second)
        : ptime(LocalDate {year, month, day}, {hour, minute, second})
    {}

    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
        : ptime(LocalDate {year, month, day}, {hour, minute, second, millisecond * 1000})
    {}

    LocalDateTime::LocalDateTime(const LocalDate& date, const LocalTime& time):
        ptime(date, time)
    {}

    LocalDateTime::LocalDateTime(const ptime& time)
        : ptime(time)
    {}

    LocalDateTime LocalDateTime::Add(const LocalDateTime& localDateTime, const Period& period)
    {
        return localDateTime + period;
    }

    int LocalDateTime::CompareTo(const LocalDateTime& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool LocalDateTime::Equals(const LocalDateTime& other) const
    {
        return *this == other;
    }

    Period LocalDateTime::Minus(const LocalDateTime& localDateTime) const
    {
        return *this - localDateTime;
    }

    LocalDateTime LocalDateTime::Minus(const Period& period) const
    {
        return *this - period;
    }

    LocalDateTime LocalDateTime::Next(int targetDayOfWeek) const
    {
        return {LocalDate(date()).Next(targetDayOfWeek), time_of_day()};
    }

    LocalDateTime LocalDateTime::Plus(const Period& period) const
    {
        return *this + period;
    }

    LocalDateTime LocalDateTime::PlusDays(int days) const
    {
        return *this + boost::gregorian::days(days);
    }

    LocalDateTime LocalDateTime::PlusHours(int64_t hours) const
    {
        return *this + boost::posix_time::hours(hours);
    }

    LocalDateTime LocalDateTime::PlusMilliseconds(int64_t milliseconds) const
    {
        return *this + boost::posix_time::milliseconds(milliseconds);
    }

    LocalDateTime LocalDateTime::PlusMinutes(int64_t minutes) const
    {
        return *this + boost::posix_time::minutes(minutes);
    }

    LocalDateTime LocalDateTime::PlusMonths(int months) const
    {
        return *this + boost::gregorian::months(months);
    }

    LocalDateTime LocalDateTime::PlusSeconds(int64_t seconds) const
    {
        return *this + boost::posix_time::seconds(seconds);
    }

    LocalDateTime LocalDateTime::PlusWeeks(int weeks) const
    {
        return *this + boost::gregorian::weeks(weeks);
    }

    LocalDateTime LocalDateTime::PlusYears(int years) const
    {
        return *this + boost::gregorian::years(years);
    }

    LocalDateTime LocalDateTime::Previous(int targetDayOfWeek) const
    {
        return {LocalDate(date()).Previous(targetDayOfWeek), time_of_day()};
    }

    Period LocalDateTime::Subtract(const LocalDateTime& lhs, const LocalDateTime& rhs)
    {
        return lhs - rhs;
    }

    LocalDateTime LocalDateTime::Subtract(const LocalDateTime& localDateTime, const Period& period)
    {
        return localDateTime - period;
    }

    LocalDateTime LocalDateTime::operator+(const Period& period) const
    {
        return static_cast<ptime>(*this) + static_cast<time_duration>(period);
    }

    bool LocalDateTime::operator==(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) == static_cast<ptime>(other);
    }

    bool LocalDateTime::operator!=(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) != static_cast<ptime>(other);
    }

    bool LocalDateTime::operator>(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) > static_cast<ptime>(other);
    }

    bool LocalDateTime::operator>=(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) >= static_cast<ptime>(other);
    }

    bool LocalDateTime::operator<(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) < static_cast<ptime>(other);
    }

    bool LocalDateTime::operator<=(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) <= static_cast<ptime>(other);
    }

    Period LocalDateTime::operator-(const LocalDateTime& other) const
    {
        return static_cast<ptime>(*this) - static_cast<ptime>(other);
    }

    LocalDateTime LocalDateTime::operator-(const Period& period) const
    {
        return static_cast<ptime>(*this) - static_cast<time_duration>(period);
    }
}