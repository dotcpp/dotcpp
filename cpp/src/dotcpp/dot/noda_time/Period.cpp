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
    period::period(const time_duration& d)
        : time_duration(d)
    {}

    period::period(const date_duration& d)
        : time_duration(24 * d.days(), 0, 0)
    {}

    period::period(const period& other)
    {
        *this = other;
    }

    period period::between(const local_date& start, const local_date& end)
    {
        return end - start;
    }

    period period::between(const local_date_time& start, const local_date_time& end)
    {
        return end - start;
    }

    period period::between(const local_time& start, const local_time& end)
    {
        return end - start;
    }

    bool period::equals(const period& other) const
    {
        return *this == other;
    }

    period period::from_days(int days)
    {
        return date_duration(days);
    }

    period period::from_hours(int64_t hours)
    {
        return boost::posix_time::hours(hours);
    }

    period period::from_milliseconds(int64_t milliseconds)
    {
        return boost::posix_time::millisec(milliseconds);
    }

    period period::from_minutes(int64_t minutes)
    {
        return boost::posix_time::minutes(minutes);
    }

    period period::from_seconds(int64_t seconds)
    {
        return boost::posix_time::seconds(seconds);
    }

    period period::from_weeks(int weeks)
    {
        return boost::gregorian::weeks(weeks);
    }

    period period::operator+(const period& other) const
    {
        return static_cast<time_duration>(*this) + static_cast<time_duration>(other);
    }

    bool period::operator==(const period & other) const
    {
        return static_cast<time_duration>(*this) == static_cast<time_duration>(other);;
    }

    bool period::operator!=(const period & other) const
    {
        return static_cast<time_duration>(*this) != static_cast<time_duration>(other);;
    }

    period period::operator-(const period & other) const
    {
        return static_cast<time_duration>(*this) - static_cast<time_duration>(other);
    }

    period::operator date_duration() const
    {
        return date_duration(base::hours() / 24);
    }
}
