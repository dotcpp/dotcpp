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
    class Period;
    class local_date;
    class LocalDateTime;
    class object;

    /// <summary>
    /// LocalTime is an immutable struct representing a time of day,
    /// with no reference to a particular calendar, time zone or date.
    /// </summary>
    class DOT_CLASS LocalTime : public ptime
    {
        typedef LocalTime self;

    public: // CONSTRUCTORS

        /// <summary>
        /// Because in C\# LocalDateTime is a struct, it has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01 00:00:00. We will
        /// replicate this behavior here.
        /// </summary>
        LocalTime();

        /// <summary>Creates a local time at the given hour and minute, with second, millisecond-of-second and tick-of-millisecond values of zero.</summary>
        LocalTime(int hour, int minute);

        /// <summary>Creates a local time at the given hour, minute and second, with millisecond-of-second and tick-of-millisecond values of zero.</summary>
        LocalTime(int hour, int minute, int second);

        /// <summary>Creates a local time at the given hour, minute, second and millisecond, with a tick-of-millisecond value of zero.</summary>
        LocalTime(int hour, int minute, int second, int millisecond);

        /// <summary>Create from Boost time_duration.</summary>
        LocalTime(const time_duration& time);

        /// <summary>Create from Boost posix_time.</summary>
        LocalTime(const ptime& time);

        /// <summary>Create from object.</summary>
        LocalTime(object const& rhs);

        /// <summary>Copy constructor.</summary>
        LocalTime(const LocalTime& other);

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
        static LocalTime Add(const LocalTime& time, const Period& period);

        /// <summary>Indicates whether this time is earlier, later or the same as another one.</summary>
        int CompareTo(const LocalTime& other) const;

        /// <summary>
        /// Compares this local time with the specified one for equality,
        /// by checking whether the two values represent the exact same local time, down to the tick.
        /// </summary>
        bool equals(const LocalTime& other) const;

        /// <summary>String that represents the current object.</summary>
        string to_string() const;

        /// <summary>Subtracts the specified time from this time, returning the result as a Period. Fluent alternative to operator-().</summary>
        Period Minus(const LocalTime& time) const;

        /// <summary>Subtracts the specified period from this time. Fluent alternative to operator-().</summary>
        LocalTime Minus(const Period& period) const;

        /// <summary>Combines this LocalTime with the given local_date into a single LocalDateTime. Fluent alternative to operator+().</summary>
        LocalDateTime On(const local_date& date);

        /// <summary>Adds the specified period to this time. Fluent alternative to operator+().</summary>
        LocalTime Plus(const Period& period) const;

        /// <summary>Returns a new LocalTime representing the current value with the given number of hours added.</summary>
        LocalTime PlusHours(int64_t hours) const;

        /// <summary>Returns a new LocalTime representing the current value with the given number of milliseconds added.</summary>
        LocalTime PlusMilliseconds(int64_t milliseconds) const;

        /// <summary>Returns a new LocalTime representing the current value with the given number of minutes added.</summary>
        LocalTime PlusMinutes(int64_t minutes) const;

        /// <summary>Returns a new LocalTime representing the current value with the given number of seconds added.</summary>
        LocalTime PlusSeconds(int64_t seconds) const;

        /// <summary>Subtracts one time from another, returning the result as a Period with units of years, months and days.</summary>
        static Period Subtract(const LocalTime& lhs, const LocalTime& rhs);

        /// <summary>Subtracts the specified period from the time. Friendly alternative to operator-().</summary>
        static LocalTime Subtract(const LocalTime& time, const Period& period);

    public:
        /// <summary>
        /// Creates a new local time by adding a period to an existing time.
        /// The period must not contain any date-related units (days etc) with non-zero values.
        /// </summary>
        LocalTime operator+(const Period& period) const;

        /// <summary>Compares two local times for equality, by checking whether they represent the exact same local time, down to the tick.</summary>
        bool operator==(const LocalTime& other) const;

        /// <summary>Compares two local times for inequality.</summary>
        bool operator!=(const LocalTime& other) const;

        /// <summary>Compares two LocalTime values to see if the left one is strictly later than the right one.</summary>
        bool operator>(const LocalTime& other) const;

        /// <summary>Compares two LocalTime values to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const LocalTime& other) const;

        /// <summary>Compares two LocalTime values to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const LocalTime& other) const;

        /// <summary>Compares two LocalTime values to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const LocalTime& other) const;

        /// <summary>Subtracts one time from another, returning the result as a Period.</summary>
        Period operator-(const LocalTime& other) const;

        /// <summary>
        /// Creates a new local time by subtracting a period from an existing time.
        /// The period must not contain any date-related units (days etc) with non-zero values.
        /// This is a convenience operator over the Minus(Period) method.
        /// </summary>
        LocalTime operator-(const Period& period) const;

    public:
        operator time_duration() const;
    };
}
