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

    /// <summary>
    /// A date and time in a particular calendar system.
    /// A local_date_time value does not represent an instant on the global time line,
    /// because it has no associated time zone: "November 12th 2009 7pm, ISO calendar"
    /// occurred at different instants for different people around the world.
    ///</summary>
    class DOT_CLASS local_date_time : public ptime
    {
        typedef local_date_time self;
        typedef ptime base;
        friend local_date;
        friend local_time;

    public: // CONSTRUCTORS

        /// <summary>
        /// In C\# local datetime is a struct, and as all structs has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01 00:00:00. Because Boost date_time
        /// library does not accept the date 0001-01-01, we will instead use the Unix epoch
        /// 1970-01-01 as default constructed value.
        /// </summary>
        local_date_time();

        /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
        local_date_time(int year, int month, int day, int hour, int minute);

        /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
        local_date_time(int year, int month, int day, int hour, int minute, int second);

        /// <summary>Initializes a new instance of the local_date_time struct using the ISO calendar system.</summary>
        local_date_time(int year, int month, int day, int hour, int minute, int second, int millisecond);

        /// <summary>Create from Boost posix_time.</summary>
        local_date_time(const ptime& time);

        /// <summary>Create from object.</summary>
        local_date_time(object const& rhs);


        /// <summary>Copy constructor.</summary>
        local_date_time(const local_date_time& other);

    private: // CONSTRUCTORS

        /// <summary>Create from date and time.</summary>
        local_date_time(const local_date& date, const local_time& time);

    public: // PROPERTIES

        /// <summary>Gets the day of this local date and time within the month.</summary>
        int day() const { return date().day(); }

        /// <summary>Gets the week day of this local date and time expressed as an IsoDayOfWeek value.</summary>
        int day_of_week() const { return date().day_of_week(); }

        /// <summary>Gets the day of this local date and time within the year.</summary>
        int day_of_year() const { return date().day_of_year(); }

        /// <summary>Gets the hour of day of this local date and time, in the range 0 to 23 inclusive.</summary>
        int hour() const { return static_cast<int>(base::time_of_day().hours()); }

        /// <summary>Gets the millisecond of this local date and time within the second, in the range 0 to 999 inclusive.</summary>
        int millisecond() const { return static_cast<int>(base::time_of_day().fractional_seconds() / 1000); }

        /// <summary>Gets the minute of this local date and time, in the range 0 to 59 inclusive.</summary>
        int minute() const { return static_cast<int>(base::time_of_day().minutes()); }

        /// <summary>Gets the month of this local date and time within the year.</summary>
        int month() const { return date().month(); }

        /// <summary>Gets the second of this local date and time within the minute, in the range 0 to 59 inclusive.</summary>
        int second() const { return static_cast<int>(base::time_of_day().seconds()); }

        /// <summary>Gets the time portion of this local date and time as a local_time.</summary>
        local_time time_of_day() const { return base::time_of_day(); }

        /// <summary>Gets the year of this local date and time.</summary>
        int year() const { return date().year(); }


    public:
        /// <summary>Add the specified period to the date and time. Friendly alternative to operator+().</summary>
        static local_date_time Add(const local_date_time& local_date_time, const period& period);

        /// <summary>Indicates whether this date/time is earlier, later or the same as another one.</summary>
        int compare_to(const local_date_time& other) const;

        /// <summary>Indicates whether the current object is equal to another object of the same type.</summary>
        bool equals(const local_date_time& other) const;

        /// <summary>String that represents the current object.</summary>
        string to_string() const;

        /// <summary>Subtracts the specified date/time from this date/time, returning the result as a period. Fluent alternative to operator-().</summary>
        period Minus(const local_date_time& local_date_time) const;

        /// <summary>Subtracts a period from a local date/time. Fields are subtracted in the order provided by the period.</summary>
        local_date_time Minus(const period& period) const;

        /// <summary>
        /// Returns the next local_date_time falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "next" - if this value on already falls on the target day of the week,
        /// the returned value will be a week later.
        ///</summary>
        local_date_time Next(int targetDayOfWeek) const;

        /// <summary>Adds a period to this local date/time. Fields are added in the order provided by the period.</summary>
        local_date_time Plus(const period& period) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of days added.</summary>
        local_date_time PlusDays(int days) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of hours added.</summary>
        local_date_time PlusHours(int64_t hours) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of milliseconds added.</summary>
        local_date_time PlusMilliseconds(int64_t milliseconds) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of minutes added.</summary>
        local_date_time PlusMinutes(int64_t minutes) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of months added.</summary>
        local_date_time PlusMonths(int months) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of seconds added.</summary>
        local_date_time PlusSeconds(int64_t seconds) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of weeks added.</summary>
        local_date_time PlusWeeks(int weeks) const;

        /// <summary>Returns a new local_date_time representing the current value with the given number of years added.</summary>
        local_date_time PlusYears(int years) const;

        /// <summary>
        /// Returns the previous local_date_time falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "previous" - if this value on already falls on the target day of the week,
        /// the returned value will be a week earlier.
        /// </summary>
        local_date_time Previous(int targetDayOfWeek) const;

        /// <summary>Subtracts one date/time from another, returning the result as a period.</summary>
        static period Subtract(const local_date_time& lhs, const local_date_time& rhs);

        /// <summary>Subtracts the specified period from the date and time. Friendly alternative to operator-().</summary>
        static local_date_time Subtract(const local_date_time& local_date_time, const period& period);

    public:
        /// <summary>
        /// Adds a period to a local date/time. Fields are added in the order provided by the period.
        /// This is a convenience operator over the Plus(period) method.
        /// </summary>
        local_date_time operator+(const period& period) const;

        /// <summary>Implements the operator == (equality).</summary>
        bool operator==(const local_date_time& other) const;

        /// <summary>Implements the operator != (inequality).</summary>
        bool operator!=(const local_date_time& other) const;

        /// <summary>Compares two local_date_time values to see if the left one is strictly later than the right one.</summary>
        bool operator>(const local_date_time& other) const;

        /// <summary>Compares two local_date_time values to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const local_date_time& other) const;

        /// <summary>Compares two local_date_time values to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const local_date_time& other) const;

        /// <summary>Compares two local_date_time values to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const local_date_time& other) const;

        /// <summary>Subtracts one date/time from another, returning the result as a period.</summary>
        period operator-(const local_date_time& other) const;

        /// <summary>
        /// Subtracts a period from a local date/time.
        /// Fields are subtracted in the order provided by the period.
        /// This is a convenience operator over the Minus(period) method.
        /// </summary>
        local_date_time operator-(const period& period) const;
    };
}
