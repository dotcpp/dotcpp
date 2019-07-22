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

#include <dot/implement.hpp>
#include <dot/nodatime/LocalMinute.hpp>
#include <dot/nodatime/LocalTime.hpp>
#include <dot/system/String.hpp>

namespace cl
{
    LocalMinute::LocalMinute(int hour, int minute)
    {
        if (hour < 0 || hour > 23) throw new_Exception(String::Format("Hour {0} specified in LocalMinute constructor is not between 0 and 23.", hour));
        if (minute < 0 || minute > 59) throw new_Exception(String::Format("Minute {0} specified in LocalMinute constructor is not between 0 and 59.", minute));

        Hour.Hour = hour;
        Minute.Minute = minute;
    }

    LocalTime LocalMinute::ToLocalTime()
    {
        return LocalTime(Hour, Minute);
    }

    int LocalMinute::CompareTo(const LocalMinute& other) const
    {
        if (MinuteOfDay > other.MinuteOfDay) return 1;
        if (MinuteOfDay < other.MinuteOfDay) return -1;
        return 0;
    }

    size_t LocalMinute::GetHashCode() const
    {
        return std::hash<int>()(MinuteOfDay);
    }

    bool LocalMinute::Equals(const LocalMinute& other) const
    {
        return *this == other;
    }

    int LocalMinute::ToIsoInt() const
    {
        // Serialized to one minute precision in ISO 8601 4 digit int hhmm format
        int result = Hour * 100 + Minute;
        return result;
    }

    String LocalMinute::ToIsoString() const
    {
        // LocalMinute is serialized to ISO 8601 string in hh:mm format
        String result = String::Format("{0:02}:{1:02}", Hour, Minute);
        return result;
    }

    bool LocalMinute::operator==(const LocalMinute& other) const
    {
        return MinuteOfDay == other.MinuteOfDay;
    }

    bool LocalMinute::operator!=(const LocalMinute& other) const
    {
        return MinuteOfDay != other.MinuteOfDay;
    }

    bool LocalMinute::operator<(const LocalMinute& other) const
    {
        return MinuteOfDay < other.MinuteOfDay;
    }

    bool LocalMinute::operator<=(const LocalMinute& other) const
    {
        return MinuteOfDay <= other.MinuteOfDay;
    }

    bool LocalMinute::operator>(const LocalMinute& other) const
    {
        return MinuteOfDay > other.MinuteOfDay;
    }

    bool LocalMinute::operator>=(const LocalMinute& other) const
    {
        return MinuteOfDay >= other.MinuteOfDay;
    }
}
