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

#include <dot/declare.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace dot
{
    using boost::posix_time::time_duration;
    using boost::gregorian::date_duration;

    class LocalTime;
    class LocalDate;
    class LocalDateTime;

    /// <summary>
    /// Represents a period of time expressed in human chronological terms:
    /// hours, days, weeks, months and so on.
    /// </summary>
    class DOT_CLASS Period : public time_duration
    {
        typedef Period self;

    public:
        Period(const time_duration& d);
        Period(const date_duration& d);

    public:
        /// <summary>Gets the number of days within this period.</summary>
        DOT_GET(int, Days, { return static_cast<int>(hours() / 24); })

        /// <summary>Gets the number of hours within this period.</summary>
        DOT_GET(int64_t, Hours, { return hours() % 24; })

        /// <summary>Gets the number of milliseconds within this period.</summary>
        DOT_GET(int64_t, Milliseconds, { return fractional_seconds() / 1000; })

        /// <summary>Gets the number of minutes within this period.</summary>
        DOT_GET(int64_t, Minutes, { return minutes(); })

        /// <summary>Gets the number of seconds within this period.</summary>
        DOT_GET(int64_t, Seconds, { return seconds(); })

    public:
        /// <summary>Returns the exact difference between two dates.</summary>
        static Period Between(const LocalDate& start, const LocalDate& end);

        /// <summary>Returns the exact difference between two date/times.</summary>
        static Period Between(const LocalDateTime& start, const LocalDateTime& end);

        /// <summary>Returns the exact difference between two times.</summary>
        static Period Between(const LocalTime& start, const LocalTime& end);

        /// <summary>Compares the given period for equality with this one.</summary>
        bool Equals(const Period& other) const;

        /// <summary>Creates a period representing the specified number of days.</summary>
        static Period FromDays(int days);

        /// <summary>Creates a period representing the specified number of hours.</summary>
        static Period FromHours(int64_t hours);

        /// <summary>Creates a period representing the specified number of milliseconds.</summary>
        static Period FromMilliseconds(int64_t milliseconds);

        /// <summary>Creates a period representing the specified number of minutes.</summary>
        static Period FromMinutes(int64_t minutes);

        /// <summary>Creates a period representing the specified number of seconds.</summary>
        static Period FromSeconds(int64_t seconds);

        /// <summary>Creates a period representing the specified number of weeks.</summary>
        static Period FromWeeks(int weeks);

    public:
        /// <summary>Adds two periods together, by simply adding the values for each property.</summary>
        Period operator+(const Period& other) const;

        /// <summary>Subtracts one period from another, by simply subtracting each property value.</summary>
        Period operator-(const Period& other) const;

        /// <summary>Compares two periods for equality.</summary>
        bool operator==(const Period& other) const;
        
        /// <summary>Compares two periods for inequality.</summary>
        bool operator!=(const Period& other) const;

    public:
        operator date_duration() const;
    };
}
