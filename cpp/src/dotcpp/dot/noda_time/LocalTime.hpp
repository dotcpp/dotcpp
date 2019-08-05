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
    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;

    class string;
    class period;
    class local_date;
    class local_date_time;
    class object;

    /// <summary>
    /// local_time is an immutable struct representing a time of day,
    /// with no reference to a particular calendar, time zone or date.
    /// </summary>
    class DOT_CLASS local_time : public ptime
    {
        typedef local_time self;

    public: // CONSTRUCTORS

        /// <summary>
        /// Because in C\# local_date_time is a struct, it has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01 00:00:00. We will
        /// replicate this behavior here.
        /// </summary>
        local_time();

        /// <summary>Creates a local time at the given hour and minute, with second, millisecond-of-second and tick-of-millisecond values of zero.</summary>
        local_time(int hour, int minute);

        /// <summary>Creates a local time at the given hour, minute and second, with millisecond-of-second and tick-of-millisecond values of zero.</summary>
        local_time(int hour, int minute, int second);

        /// <summary>Creates a local time at the given hour, minute, second and millisecond, with a tick-of-millisecond value of zero.</summary>
        local_time(int hour, int minute, int second, int millisecond);

        /// <summary>Create from Boost time_duration.</summary>
        local_time(const time_duration& time);

        /// <summary>Create from Boost posix_time.</summary>
        local_time(const ptime& time);

        /// <summary>Create from object.</summary>
        local_time(object const& rhs);

        /// <summary>Copy constructor.</summary>
        local_time(const local_time& other);

    public:
        /// <summary>Gets the hour of day of this local time, in the range 0 to 23 inclusive.</summary>
        int hour() const { return static_cast<int>(time_of_day().hours()); }

        /// <summary>Gets the millisecond of this local time within the second, in the range 0 to 999 inclusive.</summary>
        int millisecond() const { return static_cast<int>(time_of_day().fractional_seconds() / 1000); }

        /// <summary>Gets the minute of this local time, in the range 0 to 59 inclusive.</summary>
        int minute() const { return static_cast<int>(time_of_day().minutes()); }

        /// <summary>Gets the second of this local time within the minute, in the range 0 to 59 inclusive.</summary>
        int second() const { return static_cast<int>(time_of_day().seconds()); }

    public:
        /// <summary>Adds the specified period to the time. Friendly alternative to operator+().</summary>
        static local_time Add(const local_time& time, const period& period);

        /// <summary>Indicates whether this time is earlier, later or the same as another one.</summary>
        int compare_to(const local_time& other) const;

        /// <summary>
        /// Compares this local time with the specified one for equality,
        /// by checking whether the two values represent the exact same local time, down to the tick.
        /// </summary>
        bool equals(const local_time& other) const;

        /// <summary>String that represents the current object.</summary>
        string to_string() const;

        /// <summary>Subtracts the specified time from this time, returning the result as a period. Fluent alternative to operator-().</summary>
        period Minus(const local_time& time) const;

        /// <summary>Subtracts the specified period from this time. Fluent alternative to operator-().</summary>
        local_time Minus(const period& period) const;

        /// <summary>Combines this local_time with the given local_date into a single local_date_time. Fluent alternative to operator+().</summary>
        local_date_time On(const local_date& date);

        /// <summary>Adds the specified period to this time. Fluent alternative to operator+().</summary>
        local_time Plus(const period& period) const;

        /// <summary>Returns a new local_time representing the current value with the given number of hours added.</summary>
        local_time PlusHours(int64_t hours) const;

        /// <summary>Returns a new local_time representing the current value with the given number of milliseconds added.</summary>
        local_time PlusMilliseconds(int64_t milliseconds) const;

        /// <summary>Returns a new local_time representing the current value with the given number of minutes added.</summary>
        local_time PlusMinutes(int64_t minutes) const;

        /// <summary>Returns a new local_time representing the current value with the given number of seconds added.</summary>
        local_time PlusSeconds(int64_t seconds) const;

        /// <summary>Subtracts one time from another, returning the result as a period with units of years, months and days.</summary>
        static period Subtract(const local_time& lhs, const local_time& rhs);

        /// <summary>Subtracts the specified period from the time. Friendly alternative to operator-().</summary>
        static local_time Subtract(const local_time& time, const period& period);

    public:
        /// <summary>
        /// Creates a new local time by adding a period to an existing time.
        /// The period must not contain any date-related units (days etc) with non-zero values.
        /// </summary>
        local_time operator+(const period& period) const;

        /// <summary>Compares two local times for equality, by checking whether they represent the exact same local time, down to the tick.</summary>
        bool operator==(const local_time& other) const;

        /// <summary>Compares two local times for inequality.</summary>
        bool operator!=(const local_time& other) const;

        /// <summary>Compares two local_time values to see if the left one is strictly later than the right one.</summary>
        bool operator>(const local_time& other) const;

        /// <summary>Compares two local_time values to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const local_time& other) const;

        /// <summary>Compares two local_time values to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const local_time& other) const;

        /// <summary>Compares two local_time values to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const local_time& other) const;

        /// <summary>Subtracts one time from another, returning the result as a period.</summary>
        period operator-(const local_time& other) const;

        /// <summary>
        /// Creates a new local time by subtracting a period from an existing time.
        /// The period must not contain any date-related units (days etc) with non-zero values.
        /// This is a convenience operator over the Minus(period) method.
        /// </summary>
        local_time operator-(const period& period) const;

    public:
        operator time_duration() const;
    };
}
