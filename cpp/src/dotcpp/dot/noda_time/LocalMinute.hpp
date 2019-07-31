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

namespace dot
{
    class string;
    class LocalTime;

    class DOT_CLASS local_minute
    {
        typedef local_minute self;

    public: // CONSTRUCTORS

        /// <summary>Default constructor.</summary>
        local_minute() = default;

        /// <summary>
        /// Creates local time to one minute precision from the specified hour and minute.
        /// </summary>
        local_minute(int hour, int minute);

        /// <summary>Copy constructor.</summary>
        local_minute(const local_minute& other);

    public: // PROPERTIES

        /// <summary>The hour of day, in the range 0 to 23 inclusive.</summary>
        int hour() const { return hour_; }

        /// <summary>The minute of the hour, in the range 0 to 59 inclusive.</summary>
        int minute() const { return minute_; }

        /// <summary>The minute of the day, in the range 0 to 59 inclusive.</summary>
        int minute_of_day() const
        {
            return 60 * hour() + minute();
        }

    public: // METHODS

        /// <summary>Converts this local_minute to LocalTime.</summary>
        LocalTime to_local_time() const;

        /// <summary>
        /// Indicates whether this time is earlier, later or the same as another one.
        /// </summary>
        int compare_to(const local_minute& other) const;

        /// <summary>Returns a hash code for this local time.</summary>
        size_t hash_code() const;

        /// <summary>
        /// Compares this local time with the specified one for equality,
        /// by checking whether the two values represent the exact same
        /// local minute.
        /// </summary>
        bool equals(const local_minute& other) const;

        /// <summary>Convert local_minute to ISO 8601 string in hh:mm format.</summary>
        string to_string() const;

    public: // OPERATORS

        /// <summary>
        /// Compares two local times for equality, by checking whether
        /// they represent the exact same local time, down to the tick.
        /// </summary>
        bool operator==(const local_minute& other) const;

        /// <summary>Compares two local times for inequality.</summary>
        bool operator!=(const local_minute& other) const;

        /// <summary>
        /// Compares two local_minute values to see if the left one
        /// is strictly earlier than the right one.
        /// </summary>
        bool operator<(const local_minute& other) const;

        /// <summary>
        /// Compares two local_minute values to see if the left one
        /// is earlier than or equal to the right one.
        /// </summary>
        bool operator<=(const local_minute& other) const;

        /// <summary>
        /// Compares two local_minute values to see if the left one
        /// is strictly later than the right one.
        /// </summary>
        bool operator>(const local_minute& other) const;

        /// <summary>
        /// Compares two local_minute values to see if the left one
        /// is later than or equal to the right one.
        /// </summary>
        bool operator>=(const local_minute& other) const;

    private:
        int hour_;
        int minute_;
    };
}
