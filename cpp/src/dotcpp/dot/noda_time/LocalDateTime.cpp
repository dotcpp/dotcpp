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
#include <dot/system/object.hpp>
#include <dot/detail/struct_wrapper.hpp>
#include <dot/noda_time/LocalDateTime.hpp>
#include <dot/noda_time/Period.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/system/String.hpp>

namespace dot
{
    /// <summary>
    /// Because in C\# LocalDateTime is a struct, it has default constructor
    /// that initializes all backing variables to 0. This means that default
    /// constructed value corresponds to 0001-01-01 00:00:00.
    ///
    /// Because Boost date_time library does not accept the date 0001-01-01, we
    /// will instead use the Unix epoch 1970-01-01 as default constructed value.
    /// </summary>
    LocalDateTime::LocalDateTime()
        : ptime(LocalDate{ 1970, 1, 1 }, { 0, 0, 0 })
    {
    }

    /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute)
        : ptime(LocalDate {year, month, day}, {hour, minute, 0})
    {}

    /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute, int second)
        : ptime(LocalDate {year, month, day}, {hour, minute, second})
    {}

    /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
    LocalDateTime::LocalDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
        : ptime(LocalDate {year, month, day}, {hour, minute, second, millisecond * 1000})
    {}

    /// <summary>Create from Boost posix_time.</summary>
    LocalDateTime::LocalDateTime(const ptime& time)
        : ptime(time)
    {}

    LocalDateTime::LocalDateTime(const LocalDateTime& other)
    {
        *this = other;
    }

    LocalDateTime::LocalDateTime(const LocalDate& date, const LocalTime& time) :
        ptime(date, time)
    {}

    LocalDateTime::LocalDateTime(object const& rhs) { *this = rhs.operator LocalDateTime(); }

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

    String LocalDateTime::ToString() const
    {
        boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
        facet->format("%Y-%m-%d %H:%M:%S.%f");
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), facet));
        stream << *this;
        return stream.str().substr(0, 23);
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
