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

#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cl/dotcpp/main/declare.hpp>

namespace cl
{
    using gdate = boost::gregorian::date;

    class Period;
    class LocalTime;
    class LocalDateTime;

    /// <summary>
    /// LocalDate is an immutable struct representing a date within the calendar,
    /// with no reference to a particular time zone or time of day.
    /// </summary>
    class CL_DOTCPP_MAIN LocalDate : public gdate
    {
    public:
        /// <summary>Constructs an instance for the given year, month and day in the ISO calendar.</summary>
        LocalDate(int year, int month, int day);

    public:
        LocalDate();
        LocalDate(gdate date);

    public:
        /// <summary>Gets the day of this local date within the month.</summary>
        DOT_GET(LocalDate, int, Day, { return day(); })

        /// <summary>Gets the week day of this local date expressed as an IsoDayOfWeek value.</summary>
        DOT_GET(LocalDate, int, DayOfWeek, { return day_of_week(); })

        /// <summary>Gets the day of this local date within the year.</summary>
        DOT_GET(LocalDate, int, DayOfYear, { return day_of_year(); })

        /// <summary>Gets the month of this local date within the year.</summary>
        DOT_GET(LocalDate, int, Month, { return month(); })

        /// <summary>Gets the year of this local date.</summary>
        DOT_GET(LocalDate, int, Year, { return year(); })

    public:
        /// <summary>Adds the specified period to the date. Friendly alternative to operator+().</summary>
        static LocalDate Add(const LocalDate& date, const Period& period);

        /// <summary>Combines this LocalDate with the given LocalTime into a single LocalDateTime. Fluent alternative to operator+().</summary>
        LocalDateTime At(const LocalTime& time) const;

        /// <summary>Gets a LocalDateTime at midnight on the date represented by this local date.</summary>
        LocalDateTime AtMidnight() const;

        /// <summary>Indicates whether this date is earlier, later or the same as another one.</summary>
        int CompareTo(const LocalDate& other) const;

        /// <summary>Compares two LocalDate values for equality. This requires that the dates be the same, within the same calendar.</summary>
        bool Equals(const LocalDate& other) const;

        /// <summary>Subtracts the specified date from this date, returning the result as a Period with units of years, months and days. Fluent alternative to operator-().</summary>
        Period Minus(const LocalDate& date) const;

        /// <summary>Subtracts the specified period from this date. Fluent alternative to operator-().</summary>
        LocalDate Minus(const Period& period) const;

        /// <summary>
        /// Returns the next LocalDate falling on the specified IsoDayOfWeek.
        /// This is a strict "next" - if this date on already falls on the target day of the week,
        /// the returned value will be a week later.
        /// </summary>
        LocalDate Next(int targetDayOfWeek) const;

        /// <summary>Adds the specified period to this date. Fluent alternative to operator+().</summary>
        LocalDate Plus(const Period& period) const;

        /// <summary>Returns a new LocalDate representing the current value with the given number of days added.</summary>
        LocalDate PlusDays(int days) const;

        /// <summary>Returns a new LocalDate representing the current value with the given number of months added.</summary>
        LocalDate PlusMonths(int months) const;

        /// <summary>Returns a new LocalDate representing the current value with the given number of weeks added.</summary>
        LocalDate PlusWeeks(int weeks) const;

        /// <summary>Returns a new LocalDate representing the current value with the given number of years added.</summary>
        LocalDate PlusYears(int years) const;

        /// <summary>
        /// Returns the previous LocalDate falling on the specified IsoDayOfWeek.
        /// This is a strict "previous" - if this date on already falls on the
        /// target day of the week, the returned value will be a week earlier.
        /// </summary>
        LocalDate Previous(int targetDayOfWeek) const;

        /// <summary>Subtracts one date from another, returning the result as a Period with units of years, months and days.</summary>
        static Period Subtract(const LocalDate& lhs, const LocalDate& rhs);

        /// <summary>Subtracts the specified period from the date. Friendly alternative to operator-().</summary>
        static LocalDate Subtract(const LocalDate& date, const Period& period);

    public:
        /// <summary>Combines the given LocalDate and LocalTime components into a single LocalDateTime.</summary>
        LocalDateTime operator+(const LocalTime& time) const;

        /// <summary>Adds the specified period to the date.</summary>
        LocalDate operator+(const Period& period) const;

        /// <summary>Compares two LocalDate values for equality. This requires that the dates be the same, within the same calendar.</summary>
        bool operator==(const LocalDate& other) const;

        /// <summary>Compares two LocalDate values for inequality.</summary>
        bool operator!=(const LocalDate& other) const;

        /// <summary>Compares two dates to see if the left one is strictly later than the right one.</summary>
        bool operator>(const LocalDate& other) const;

        /// <summary>Compares two dates to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const LocalDate& other) const;

        /// <summary>Compares two dates to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const LocalDate& other) const;

        /// <summary>Compares two dates to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const LocalDate& other) const;

        /// <summary>Subtracts one date from another, returning the result as a Period with units of years, months and days.</summary>
        Period operator-(const LocalDate& other) const;

        /// <summary>Subtracts the specified period from the date. This is a convenience operator over the Minus(Period) method.</summary>
        LocalDate operator-(const Period& period) const;
    };
}
