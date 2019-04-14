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

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/LocalTime.hpp>
#include <cl/dotcpp/main/system/LocalDate.hpp>

namespace cl
{
    using boost::posix_time::ptime;

    class Period;

    /// <summary>
    /// A date and time in a particular calendar system.
    /// A LocalDateTime value does not represent an instant on the global time line,
    /// because it has no associated time zone: "November 12th 2009 7pm, ISO calendar"
    /// occurred at different instants for different people around the world.
    ///</summary>
    class CL_DOTCPP_MAIN LocalDateTime : public ptime
    {
        typedef LocalDateTime self;

    public: // CONSTRUCTORS

        /// <summary>Initializes to default value that the code will treat as empty.</summary>
        LocalDateTime();

        /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
        LocalDateTime(int year, int month, int day, int hour, int minute);

        /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
        LocalDateTime(int year, int month, int day, int hour, int minute, int second);

        /// <summary>Initializes a new instance of the LocalDateTime struct using the ISO calendar system.</summary>
        LocalDateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);

    public:
        LocalDateTime(const LocalDate& date, const LocalTime& time);
        LocalDateTime(const ptime& time);

    public:
        /// <summary>Gets the day of this local date within the month.</summary>
        DOT_GET(LocalDate, Date, { return date(); })

        /// <summary>Gets the day of this local date and time within the month.</summary>
        DOT_GET(int, Day, { return date().day(); })

        /// <summary>Gets the week day of this local date and time expressed as an IsoDayOfWeek value.</summary>
        DOT_GET(int, DayOfWeek, { return date().day_of_week(); })

        /// <summary>Gets the day of this local date and time within the year.</summary>
        DOT_GET(int, DayOfYear, { return date().day_of_year(); })

        /// <summary>Gets the hour of day of this local date and time, in the range 0 to 23 inclusive.</summary>
        DOT_GET(int, Hour, { return static_cast<int>(time_of_day().hours()); })

        /// <summary>Gets the millisecond of this local date and time within the second, in the range 0 to 999 inclusive.</summary>
        DOT_GET(int, Millisecond, { return static_cast<int>(time_of_day().fractional_seconds() / 1000); })

        /// <summary>Gets the minute of this local date and time, in the range 0 to 59 inclusive.</summary>
        DOT_GET(int, Minute, { return static_cast<int>(time_of_day().minutes()); })

        /// <summary>Gets the month of this local date and time within the year.</summary>
        DOT_GET(int, Month, { return date().month(); })

        /// <summary>Gets the second of this local date and time within the minute, in the range 0 to 59 inclusive.</summary>
        DOT_GET(int, Second, { return static_cast<int>(time_of_day().seconds()); })

        /// <summary>Gets the time portion of this local date and time as a LocalTime.</summary>
        DOT_GET(LocalTime, TimeOfDay, { return time_of_day(); })

        /// <summary>Gets the year of this local date and time.</summary>
        DOT_GET(int, Year, { return date().year(); })


    public:
        /// <summary>Add the specified period to the date and time. Friendly alternative to operator+().</summary>
        static LocalDateTime Add(const LocalDateTime& localDateTime, const Period& period);

        /// <summary>Indicates whether this date/time is earlier, later or the same as another one.</summary>
        int CompareTo(const LocalDateTime& other) const;

        /// <summary>Indicates whether the current object is equal to another object of the same type.</summary>
        bool Equals(const LocalDateTime& other) const;

        /// <summary>Subtracts the specified date/time from this date/time, returning the result as a Period. Fluent alternative to operator-().</summary>
        Period Minus(const LocalDateTime& localDateTime) const;

        /// <summary>Subtracts a period from a local date/time. Fields are subtracted in the order provided by the period.</summary>
        LocalDateTime Minus(const Period& period) const;

        /// <summary>
        /// Returns the next LocalDateTime falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "next" - if this value on already falls on the target day of the week,
        /// the returned value will be a week later.
        ///</summary>
        LocalDateTime Next(int targetDayOfWeek) const;

        /// <summary>Adds a period to this local date/time. Fields are added in the order provided by the period.</summary>
        LocalDateTime Plus(const Period& period) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of days added.</summary>
        LocalDateTime PlusDays(int days) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of hours added.</summary>
        LocalDateTime PlusHours(int64_t hours) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of milliseconds added.</summary>
        LocalDateTime PlusMilliseconds(int64_t milliseconds) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of minutes added.</summary>
        LocalDateTime PlusMinutes(int64_t minutes) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of months added.</summary>
        LocalDateTime PlusMonths(int months) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of seconds added.</summary>
        LocalDateTime PlusSeconds(int64_t seconds) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of weeks added.</summary>
        LocalDateTime PlusWeeks(int weeks) const;

        /// <summary>Returns a new LocalDateTime representing the current value with the given number of years added.</summary>
        LocalDateTime PlusYears(int years) const;

        /// <summary>
        /// Returns the previous LocalDateTime falling on the specified IsoDayOfWeek, at the same time of day as this value.
        /// This is a strict "previous" - if this value on already falls on the target day of the week,
        /// the returned value will be a week earlier.
        /// </summary>
        LocalDateTime Previous(int targetDayOfWeek) const;

        /// <summary>Subtracts one date/time from another, returning the result as a Period.</summary>
        static Period Subtract(const LocalDateTime& lhs, const LocalDateTime& rhs);

        /// <summary>Subtracts the specified period from the date and time. Friendly alternative to operator-().</summary>
        static LocalDateTime Subtract(const LocalDateTime& localDateTime, const Period& period);

    public:
        /// <summary>
        /// Adds a period to a local date/time. Fields are added in the order provided by the period.
        /// This is a convenience operator over the Plus(Period) method.
        /// </summary>
        LocalDateTime operator+(const Period& period) const;

        /// <summary>Implements the operator == (equality).</summary>
        bool operator==(const LocalDateTime& other) const;

        /// <summary>Implements the operator != (inequality).</summary>
        bool operator!=(const LocalDateTime& other) const;

        /// <summary>Compares two LocalDateTime values to see if the left one is strictly later than the right one.</summary>
        bool operator>(const LocalDateTime& other) const;

        /// <summary>Compares two LocalDateTime values to see if the left one is later than or equal to the right one.</summary>
        bool operator>=(const LocalDateTime& other) const;

        /// <summary>Compares two LocalDateTime values to see if the left one is strictly earlier than the right one.</summary>
        bool operator<(const LocalDateTime& other) const;

        /// <summary>Compares two LocalDateTime values to see if the left one is earlier than or equal to the right one.</summary>
        bool operator<=(const LocalDateTime& other) const;

        /// <summary>Subtracts one date/time from another, returning the result as a Period.</summary>
        Period operator-(const LocalDateTime& other) const;

        /// <summary>
        /// Subtracts a period from a local date/time.
        /// Fields are subtracted in the order provided by the period.
        /// This is a convenience operator over the Minus(Period) method.
        /// </summary>
        LocalDateTime operator-(const Period& period) const;
    };
}
