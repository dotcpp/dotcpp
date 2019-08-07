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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/local_date.hpp>

namespace dot
{
    using boost::posix_time::ptime;

    class string;
    class period;
    class object;

    /// A date and time in a particular calendar system.
    /// A local_date_time value does not represent an instant on the global time line,
    /// because it has no associated time zone: "November 12th 2009 7pm, ISO calendar"
    /// occurred at different instants for different people around the world.
    ///
    class DOT_CLASS local_date_time : public ptime
    {
        typedef local_date_time self;
        typedef ptime base;
        friend local_date;
        friend local_time;

    public: // CONSTRUCTORS

        /// In C\# local datetime is a struct, and as all structs has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01 00:00:00. Because Boost date_time
        /// library does not accept the date 0001-01-01, we will instead use the Unix epoch
        /// 1970-01-01 as default constructed value.
        local_date_time();

        /// Initializes a new instance of the local_date_time struct using the ISO calendar system.
        local_date_time(int year, int month, int day, int hour, int minute);

        /// Initializes a new instance of the local_date_time struct using the ISO calendar system.
        local_date_time(int year, int month, int day, int hour, int minute, int second);

        /// Initializes a new instance of the local_date_time struct using the ISO calendar system.
        local_date_time(int year, int month, int day, int hour, int minute, int second, int millisecond);

        /// Create from Boost posix_time.
        local_date_time(const ptime& time);

        /// Create from object.
        local_date_time(object const& rhs);


        /// Copy constructor.
        local_date_time(const local_date_time& other);

    private: // CONSTRUCTORS

        /// Create from date and time.
        local_date_time(const local_date& date, const local_time& time);

    public: // PROPERTIES

        /// Gets the day of this local date and time within the month.
        int day() const { return date().day(); }

        /// Gets the week day of this local date and time expressed as an IsoDayOfWeek value.
        int day_of_week() const { return date().day_of_week(); }

        /// Gets the day of this local date and time within the year.
        int day_of_year() const { return date().day_of_year(); }

        /// Gets the hour of day of this local date and time, in the range 0 to 23 inclusive.
        int hour() const { return static_cast<int>(base::time_of_day().hours()); }

        /// Gets the millisecond of this local date and time within the second, in the range 0 to 999 inclusive.
        int millisecond() const { return static_cast<int>(base::time_of_day().fractional_seconds() / 1000); }

        /// Gets the minute of this local date and time, in the range 0 to 59 inclusive.
        int minute() const { return static_cast<int>(base::time_of_day().minutes()); }

        /// Gets the month of this local date and time within the year.
        int month() const { return date().month(); }

        /// Gets the second of this local date and time within the minute, in the range 0 to 59 inclusive.
        int second() const { return static_cast<int>(base::time_of_day().seconds()); }

        /// Gets the time portion of this local date and time as a local_time.
        local_time time_of_day() const { return base::time_of_day(); }

        /// Gets the year of this local date and time.
        int year() const { return date().year(); }


    public:
        /// Add the specified period to the date and time. Friendly alternative to operator+().
        static local_date_time Add(const local_date_time& local_date_time, const period& period);

        /// Indicates whether this date/time is earlier, later or the same as another one.
        int compare_to(const local_date_time& other) const;

        /// Indicates whether the current object is equal to another object of the same type.
        bool equals(const local_date_time& other) const;

        /// String that represents the current object.
        string to_string() const;

        /// Subtracts the specified date/time from this date/time, returning the result as a period. Fluent alternative to operator-().
        period Minus(const local_date_time& local_date_time) const;

        /// Subtracts a period from a local date/time. Fields are subtracted in the order provided by the period.
        local_date_time Minus(const period& period) const;

        /// Returns the next local_date_time falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "next" - if this value on already falls on the target day of the week,
        /// the returned value will be a week later.
        ///
        local_date_time Next(int targetDayOfWeek) const;

        /// Adds a period to this local date/time. Fields are added in the order provided by the period.
        local_date_time Plus(const period& period) const;

        /// Returns a new local_date_time representing the current value with the given number of days added.
        local_date_time PlusDays(int days) const;

        /// Returns a new local_date_time representing the current value with the given number of hours added.
        local_date_time PlusHours(int64_t hours) const;

        /// Returns a new local_date_time representing the current value with the given number of milliseconds added.
        local_date_time PlusMilliseconds(int64_t milliseconds) const;

        /// Returns a new local_date_time representing the current value with the given number of minutes added.
        local_date_time PlusMinutes(int64_t minutes) const;

        /// Returns a new local_date_time representing the current value with the given number of months added.
        local_date_time PlusMonths(int months) const;

        /// Returns a new local_date_time representing the current value with the given number of seconds added.
        local_date_time PlusSeconds(int64_t seconds) const;

        /// Returns a new local_date_time representing the current value with the given number of weeks added.
        local_date_time PlusWeeks(int weeks) const;

        /// Returns a new local_date_time representing the current value with the given number of years added.
        local_date_time PlusYears(int years) const;

        /// Returns the previous local_date_time falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "previous" - if this value on already falls on the target day of the week,
        /// the returned value will be a week earlier.
        local_date_time Previous(int targetDayOfWeek) const;

        /// Subtracts one date/time from another, returning the result as a period.
        static period Subtract(const local_date_time& lhs, const local_date_time& rhs);

        /// Subtracts the specified period from the date and time. Friendly alternative to operator-().
        static local_date_time Subtract(const local_date_time& local_date_time, const period& period);

    public:
        /// Adds a period to a local date/time. Fields are added in the order provided by the period.
        /// This is a convenience operator over the Plus(period) method.
        local_date_time operator+(const period& period) const;

        /// Implements the operator == (equality).
        bool operator==(const local_date_time& other) const;

        /// Implements the operator != (inequality).
        bool operator!=(const local_date_time& other) const;

        /// Compares two local_date_time values to see if the left one is strictly later than the right one.
        bool operator>(const local_date_time& other) const;

        /// Compares two local_date_time values to see if the left one is later than or equal to the right one.
        bool operator>=(const local_date_time& other) const;

        /// Compares two local_date_time values to see if the left one is strictly earlier than the right one.
        bool operator<(const local_date_time& other) const;

        /// Compares two local_date_time values to see if the left one is earlier than or equal to the right one.
        bool operator<=(const local_date_time& other) const;

        /// Subtracts one date/time from another, returning the result as a period.
        period operator-(const local_date_time& other) const;

        /// Subtracts a period from a local date/time.
        /// Fields are subtracted in the order provided by the period.
        /// This is a convenience operator over the Minus(period) method.
        local_date_time operator-(const period& period) const;
    };
}
