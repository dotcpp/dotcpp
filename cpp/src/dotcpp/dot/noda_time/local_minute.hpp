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
    class local_time;

    class DOT_CLASS local_minute
    {
        typedef local_minute self;

    public: // CONSTRUCTORS

        /// Default constructor.
        local_minute() = default;

        /// 
        /// Creates local time to one minute precision from the specified hour and minute.
        /// 
        local_minute(int hour, int minute);

        /// Copy constructor.
        local_minute(const local_minute& other);

    public: // PROPERTIES

        /// The hour of day, in the range 0 to 23 inclusive.
        int hour() const { return hour_; }

        /// The minute of the hour, in the range 0 to 59 inclusive.
        int minute() const { return minute_; }

        /// The minute of the day, in the range 0 to 59 inclusive.
        int minute_of_day() const
        {
            return 60 * hour() + minute();
        }

    public: // METHODS

        /// Converts this local_minute to local_time.
        local_time to_local_time() const;

        /// 
        /// Indicates whether this time is earlier, later or the same as another one.
        /// 
        int compare_to(const local_minute& other) const;

        /// Returns a hash code for this local time.
        size_t hash_code() const;

        /// 
        /// Compares this local time with the specified one for equality,
        /// by checking whether the two values represent the exact same
        /// local minute.
        /// 
        bool equals(const local_minute& other) const;

        /// Convert local_minute to ISO 8601 string in hh:mm format.
        string to_string() const;

    public: // OPERATORS

        /// 
        /// Compares two local times for equality, by checking whether
        /// they represent the exact same local time, down to the tick.
        /// 
        bool operator==(const local_minute& other) const;

        /// Compares two local times for inequality.
        bool operator!=(const local_minute& other) const;

        /// 
        /// Compares two local_minute values to see if the left one
        /// is strictly earlier than the right one.
        /// 
        bool operator<(const local_minute& other) const;

        /// 
        /// Compares two local_minute values to see if the left one
        /// is earlier than or equal to the right one.
        /// 
        bool operator<=(const local_minute& other) const;

        /// 
        /// Compares two local_minute values to see if the left one
        /// is strictly later than the right one.
        /// 
        bool operator>(const local_minute& other) const;

        /// 
        /// Compares two local_minute values to see if the left one
        /// is later than or equal to the right one.
        /// 
        bool operator>=(const local_minute& other) const;

    private:
        int hour_;
        int minute_;
    };
}
