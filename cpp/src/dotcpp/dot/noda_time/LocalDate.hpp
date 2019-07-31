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
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace dot
{
    using gdate = boost::gregorian::date;

    class string;
    class Period;
    class LocalTime;
    class LocalDateTime;
    class object;

    /// <summary>
    /// local_date is an immutable struct representing a date within the calendar,
    /// with no reference to a particular time zone or time of day.
    /// </summary>
    class DOT_CLASS local_date : public gdate
    {
        typedef local_date self;

    public: // CONSTRUCTORS

        /// <summary>
        /// In C\# local date is a struct, and as all structs it has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01. As Boost date_time library
        /// does not accept the date 0001-01-01, we will instead use the Unix epoch
        /// 1970-01-01 as default constructed value.
        /// </summary>
        local_date();

        /// <summary>Constructs an instance for the given year, month and day in the ISO calendar.</summary>
        local_date(int year, int month, int day);

        /// <summary>Create from Boost gregorian date.</summary>
        local_date(gdate date);

        /// <summary>Copy constructor.</summary>
        local_date(const local_date& other);

        /// <summary>Create from object.</summary>
        local_date(object const& rhs);

    public:
        /// <summary>Adds the specified period to the date. Friendly alternative to operator+().</summary>
        static local_date Add(const local_date& date, const Period& period);

        /// <summary>Combines this local_date with the given LocalTime into a single LocalDateTime. Fluent alternative to operator+().</summary>
        LocalDateTime At(const LocalTime& time) const;

        /// <summary>Gets a LocalDateTime at midnight on the date represented by this local date.</summary>
        LocalDateTime AtMidnight() const;

        /// <summary>Indicates whether this date is earlier, later or the same as another one.</summary>
        int CompareTo(const local_date& other) const;

        /// <summary>Compares two local_date values for equality. This requires that the dates be the same, within the same calendar.</summary>
        bool equals(const local_date& other) const;

        /// <summary>String that represents the current object.</summary>
        string to_string() const;

        /// <summary>Subtracts the specified date from this date, returning the result as a Period with units of years, months and days. Fluent alternative to operator-().</summary>
        Period Minus(const local_date& date) const;

        /// <summary>Subtracts the specified period from this date. Fluent alternative to operator-().</summary>
        local_date Minus(const Period& period) const;

        /// <summary>
        /// Returns the next local_date falling on the specified IsoDayOfWeek.
        /// This is a strict "next" - if this date on already falls on the target day of the week,
        /// the returned value will be a week later.
        /// </summary>
        local_date Next(int targetDayOfWeek) const;

        /// <summary>Adds the specified period to this date. Fluent alternative to operator+().</summary>
        local_date Plus(const Period& period) const;

        /// <summary>Returns a new local_date representing the current value with the given number of days added.</summary>
        local_date PlusDays(int days) const;

        /// <summary>Returns a new local_date representing the current value with the given number of months added.</summary>
        local_date PlusMonths(int months) const;

        /// <summary>Returns a new local_date representing the current value with the given number of weeks added.</summary>
        local_date PlusWeeks(int weeks) const;

        /// <summary>Returns a new local_date representing the current value with the given number of years added.</summary>
        local_date PlusYears(int years) const;

        /// <summary>
        /// Returns the previous local_date falling on the specified IsoDayOfWeek.
        /// This is a strict "previous" - if this date on already falls on the
        /// target day of the week, the returned value will be a week earlier.
        /// </summary>
        local_date Previous(int targetDayOfWeek) const;

        /// <summary>Subtracts one date from another, returning the result as a Period with units of years, months and days.</summary>
        static Period Subtract(const local_date& lhs, const local_date& rhs);

        /// <summary>Subtracts the specified period from the date. Friendly alternative to operator-().</summary>
        static local_date Subtract(const local_date& date, const Period& period);

    public:
        /// <summary>Combines the given local_date and LocalTime components into a single LocalDateTime.</summary>
        LocalDateTime operator+(const LocalTime& time) const;

        /// <summary>Adds the specified period to the date.</summary>
        local_date operator+(const Period& period) const;

        /// <summary>Compares two local_date values for equality. This requires that the dates be the same, within the same calendar.</summary>
        bool operator==(const local_date& other) const;

        /// <summary>Compares two local_date values for inequality.</summary>
        bool operator!=(const local_date& other) const;

        /// <summary>Compares two dates to see if the left one is strictly later than the right one.</summary>
        bool operator>(const local_date& other) const;

        /// <summary>Compares two dates to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const local_date& other) const;

        /// <summary>Compares two dates to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const local_date& other) const;

        /// <summary>Compares two dates to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const local_date& other) const;

        /// <summary>Subtracts one date from another, returning the result as a Period with units of years, months and days.</summary>
        Period operator-(const local_date& other) const;

        /// <summary>Subtracts the specified period from the date. This is a convenience operator over the Minus(Period) method.</summary>
        local_date operator-(const Period& period) const;
    };
}
