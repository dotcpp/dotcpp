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
    class period;
    class local_time;
    class local_date_time;
    class object;

    /// 
    /// local_date is an immutable struct representing a date within the calendar,
    /// with no reference to a particular time zone or time of day.
    /// 
    class DOT_CLASS local_date : public gdate
    {
        typedef local_date self;

    public: // CONSTRUCTORS

        /// 
        /// In C\# local date is a struct, and as all structs it has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01. As Boost date_time library
        /// does not accept the date 0001-01-01, we will instead use the Unix epoch
        /// 1970-01-01 as default constructed value.
        /// 
        local_date();

        /// Constructs an instance for the given year, month and day in the ISO calendar.
        local_date(int year, int month, int day);

        /// Create from Boost gregorian date.
        local_date(gdate date);

        /// Copy constructor.
        local_date(const local_date& other);

        /// Create from object.
        local_date(object const& rhs);

    public:
        /// Adds the specified period to the date. Friendly alternative to operator+().
        static local_date add(const local_date& date, const period& period);

        /// Combines this local_date with the given local_time into a single local_date_time. Fluent alternative to operator+().
        local_date_time at(const local_time& time) const;

        /// Gets a local_date_time at midnight on the date represented by this local date.
        local_date_time at_midnight() const;

        /// Indicates whether this date is earlier, later or the same as another one.
        int compare_to(const local_date& other) const;

        /// Compares two local_date values for equality. This requires that the dates be the same, within the same calendar.
        bool equals(const local_date& other) const;

        /// String that represents the current object.
        string to_string() const;

        /// Subtracts the specified date from this date, returning the result as a period with units of years, months and days. Fluent alternative to operator-().
        period minus(const local_date& date) const;

        /// Subtracts the specified period from this date. Fluent alternative to operator-().
        local_date minus(const period& period) const;

        /// 
        /// Returns the next local_date falling on the specified IsoDayOfWeek.
        /// This is a strict "next" - if this date on already falls on the target day of the week,
        /// the returned value will be a week later.
        /// 
        local_date next(int target_day_of_week) const;

        /// Adds the specified period to this date. Fluent alternative to operator+().
        local_date plus(const period& period) const;

        /// Returns a new local_date representing the current value with the given number of days added.
        local_date plus_days(int days) const;

        /// Returns a new local_date representing the current value with the given number of months added.
        local_date plus_months(int months) const;

        /// Returns a new local_date representing the current value with the given number of weeks added.
        local_date plus_weeks(int weeks) const;

        /// Returns a new local_date representing the current value with the given number of years added.
        local_date plus_years(int years) const;

        /// 
        /// Returns the previous local_date falling on the specified IsoDayOfWeek.
        /// This is a strict "previous" - if this date on already falls on the
        /// target day of the week, the returned value will be a week earlier.
        /// 
        local_date previous(int target_day_of_week) const;

        /// Subtracts one date from another, returning the result as a period with units of years, months and days.
        static period subtract(const local_date& lhs, const local_date& rhs);

        /// Subtracts the specified period from the date. Friendly alternative to operator-().
        static local_date subtract(const local_date& date, const period& period);

    public:
        /// Combines the given local_date and local_time components into a single local_date_time.
        local_date_time operator+(const local_time& time) const;

        /// Adds the specified period to the date.
        local_date operator+(const period& period) const;

        /// Compares two local_date values for equality. This requires that the dates be the same, within the same calendar.
        bool operator==(const local_date& other) const;

        /// Compares two local_date values for inequality.
        bool operator!=(const local_date& other) const;

        /// Compares two dates to see if the left one is strictly later than the right one.
        bool operator>(const local_date& other) const;

        /// Compares two dates to see if the left one is later than or equal to the right one.
        bool operator>=(const local_date& other) const;

        /// Compares two dates to see if the left one is strictly earlier than the right one.
        bool operator<(const local_date& other) const;

        /// Compares two dates to see if the left one is earlier than or equal to the right one.
        bool operator<=(const local_date& other) const;

        /// Subtracts one date from another, returning the result as a period with units of years, months and days.
        period operator-(const local_date& other) const;

        /// Subtracts the specified period from the date. This is a convenience operator over the Minus(period) method.
        local_date operator-(const period& period) const;
    };
}
