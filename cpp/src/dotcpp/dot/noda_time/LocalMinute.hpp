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

namespace dot
{
    class String;
    class LocalTime;

    class CL_DOTCPP_MAIN LocalMinute
    {
        typedef LocalMinute self;

    public: // CONSTRUCTORS

        /// <summary>
        /// Creates local time to one minute precision from the specified hour and minute.
        /// </summary>
        LocalMinute(int hour, int minute);

    public: // PROPERTIES

        /// <summary>The hour of day, in the range 0 to 23 inclusive.</summary>
        DOT_AUTO_GET(int, Hour)

        /// <summary>The minute of the hour, in the range 0 to 59 inclusive.</summary>
        DOT_AUTO_GET(int, Minute)

        /// <summary>The minute of the day, in the range 0 to 59 inclusive.</summary>
        DOT_GET(int, MinuteOfDay,
        {
            return 60 * this->Hour + this->Minute;
        })

    public: // METHODS

        /// <summary>Converts this LocalMinute to LocalTime.</summary>
        LocalTime ToLocalTime();

        /// <summary>
        /// Indicates whether this time is earlier, later or the same as another one.
        /// </summary>
        int CompareTo(const LocalMinute& other) const;

        /// <summary>Returns a hash code for this local time.</summary>
        size_t GetHashCode() const;

        /// <summary>
        /// Compares this local time with the specified one for equality,
        /// by checking whether the two values represent the exact same
        /// local minute.
        /// </summary>
        bool Equals(const LocalMinute& other) const;

        /// <summary>Convert LocalMinute to ISO 8601 4 digit int hhmm format.</summary>
        int ToIsoInt() const;

        /// <summary>Convert LocalMinute to ISO 8601 string in hh:mm format.</summary>
        String ToIsoString() const;

    public: // OPERATORS

        /// <summary>
        /// Compares two local times for equality, by checking whether
        /// they represent the exact same local time, down to the tick.
        /// </summary>
        bool operator==(const LocalMinute& other) const;

        /// <summary>Compares two local times for inequality.</summary>
        bool operator!=(const LocalMinute& other) const;

        /// <summary>
        /// Compares two LocalMinute values to see if the left one
        /// is strictly earlier than the right one.
        /// </summary>
        bool operator<(const LocalMinute& other) const;

        /// <summary>
        /// Compares two LocalMinute values to see if the left one
        /// is earlier than or equal to the right one.
        /// </summary>
        bool operator<=(const LocalMinute& other) const;

        /// <summary>
        /// Compares two LocalMinute values to see if the left one
        /// is strictly later than the right one.
        /// </summary>
        bool operator>(const LocalMinute& other) const;

        /// <summary>
        /// Compares two LocalMinute values to see if the left one
        /// is later than or equal to the right one.
        /// </summary>
        bool operator>=(const LocalMinute& other) const;
    };
}
