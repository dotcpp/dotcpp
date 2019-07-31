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

#include <dot/implement.hpp>
#include <dot/noda_time/Period.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalDateTime.hpp>

namespace dot
{
    Period::Period(const time_duration& d)
        : time_duration(d)
    {}

    Period::Period(const date_duration& d)
        : time_duration(24 * d.days(), 0, 0)
    {}

    Period::Period(const Period& other)
    {
        *this = other;
    }

    Period Period::Between(const local_date& start, const local_date& end)
    {
        return end - start;
    }

    Period Period::Between(const LocalDateTime& start, const LocalDateTime& end)
    {
        return end - start;
    }

    Period Period::Between(const LocalTime& start, const LocalTime& end)
    {
        return end - start;
    }

    bool Period::equals(const Period& other) const
    {
        return *this == other;
    }

    Period Period::FromDays(int days)
    {
        return date_duration(days);
    }

    Period Period::FromHours(int64_t hours)
    {
        return boost::posix_time::hours(hours);
    }

    Period Period::FromMilliseconds(int64_t milliseconds)
    {
        return boost::posix_time::millisec(milliseconds);
    }

    Period Period::FromMinutes(int64_t minutes)
    {
        return boost::posix_time::minutes(minutes);
    }

    Period Period::FromSeconds(int64_t seconds)
    {
        return boost::posix_time::seconds(seconds);
    }

    Period Period::FromWeeks(int weeks)
    {
        return boost::gregorian::weeks(weeks);
    }

    Period Period::operator+(const Period& other) const
    {
        return static_cast<time_duration>(*this) + static_cast<time_duration>(other);
    }

    bool Period::operator==(const Period & other) const
    {
        return static_cast<time_duration>(*this) == static_cast<time_duration>(other);;
    }

    bool Period::operator!=(const Period & other) const
    {
        return static_cast<time_duration>(*this) != static_cast<time_duration>(other);;
    }

    Period Period::operator-(const Period & other) const
    {
        return static_cast<time_duration>(*this) - static_cast<time_duration>(other);
    }

    Period::operator date_duration() const
    {
        return date_duration(base::hours() / 24);
    }
}
