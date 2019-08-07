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

namespace dot
{
    using boost::posix_time::time_duration;
    using boost::gregorian::date_duration;

    class local_time;
    class local_date;
    class local_date_time;
    class object;

    /// 
    /// Represents a period of time expressed in human chronological terms:
    /// hours, days, weeks, months and so on.
    /// 
    class DOT_CLASS period : public time_duration
    {
        typedef period self;
        typedef time_duration base;

    public:
        period(const time_duration& d);
        period(const date_duration& d);

        /// Copy constructor.
        period(const period& other);

    public:
        /// Gets the number of days within this period.
        int days() const
        {
            return static_cast<int>(base::hours() / 24);
        }

        /// Gets the number of hours within this period.
        int64_t hours() const
        {
            return base::hours() % 24; // base::hours() returns total number of hours
        }

        /// Gets the number of milliseconds within this period.
        int64_t milliseconds() const
        {
            return fractional_seconds() / 1000;
        }

    public:
        /// Returns the exact difference between two dates.
        static period between(const local_date& start, const local_date& end);

        /// Returns the exact difference between two date/times.
        static period between(const local_date_time& start, const local_date_time& end);

        /// Returns the exact difference between two times.
        static period between(const local_time& start, const local_time& end);

        /// Compares the given period for equality with this one.
        bool equals(const period& other) const;

        /// Creates a period representing the specified number of days.
        static period from_days(int days);

        /// Creates a period representing the specified number of hours.
        static period from_hours(int64_t hours);

        /// Creates a period representing the specified number of milliseconds.
        static period from_milliseconds(int64_t milliseconds);

        /// Creates a period representing the specified number of minutes.
        static period from_minutes(int64_t minutes);

        /// Creates a period representing the specified number of seconds.
        static period from_seconds(int64_t seconds);

        /// Creates a period representing the specified number of weeks.
        static period from_weeks(int weeks);

    public:
        /// Adds two periods together, by simply adding the values for each property.
        period operator+(const period& other) const;

        /// Subtracts one period from another, by simply subtracting each property value.
        period operator-(const period& other) const;

        /// Compares two periods for equality.
        bool operator==(const period& other) const;

        /// Compares two periods for inequality.
        bool operator!=(const period& other) const;

    public:
        operator date_duration() const;
    };
}
