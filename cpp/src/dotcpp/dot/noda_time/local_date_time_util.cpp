/*
Copyright (C) 2013-present The DataCentric Authors.

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

#include <dot/precompiled.hpp>
#include <dot/implement.hpp>
#include <dot/noda_time/local_date_time_util.hpp>
#include <dot/system/exception.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    dot::local_date_time local_date_time_util::Parse(dot::string value)
    {
        boost::posix_time::time_input_facet* facet = new boost::posix_time::time_input_facet();
        facet->format("%Y-%m-%d %H:%M:%S%f");
        std::istringstream stream(*value);
        stream.imbue(std::locale(std::locale::classic(), facet));

        boost::posix_time::ptime ptime;
        stream >> ptime;

        // If default constructed datetime is passed, error message
        if (ptime == boost::posix_time::not_a_date_time) throw dot::exception(dot::string::format(
            "String representation of default constructed datetime {0} "
            "passed to local_date_time.Parse(datetime) method.", value));

        return ptime;
    }

    int64_t local_date_time_util::ToIsoLong(dot::local_date_time value)
    {
        // local_date_time is serialized as readable ISO int64 in yyyymmddhhmmsssss format
        int isoDate = value.year() * 10'000 + value.month() * 100 + value.day();
        int isoTime = value.hour() * 100'00'000 + value.minute() * 100'000 + value.second() * 1000 + value.millisecond();
        int64_t result = ((int64_t)isoDate) * 100'00'00'000 + (int64_t)isoTime;
        return result;
    }

    dot::local_date_time local_date_time_util::ParseIsoLong(int64_t value)
    {
        // Split into date and time using int64 arithmetic
        int64_t isoDateLong = value / 100'00'00'000;
        int64_t isoTimeLong = value - 100'00'00'000 * isoDateLong;

        // Check that it will fit into Int32 range
        if (isoDateLong < INT32_MIN || isoDateLong > INT32_MAX)
            throw dot::exception(dot::string::format("Date portion of datetime {0} has invalid format.", value));
        if (isoTimeLong < INT32_MIN || isoTimeLong > INT32_MAX)
            throw dot::exception(dot::string::format("Time portion of datetime {0} has invalid format.", value));

        // Convert to Int32
        int isoDate = (int)isoDateLong;
        int isoTime = (int)isoTimeLong;

        // Extract year, month, day
        int year = isoDate / 100'00;
        isoDate -= year * 100'00;
        int month = isoDate / 100;
        isoDate -= month * 100;
        int day = isoDate;

        // Extract year, month, day
        int hour = isoTime / 100'00'000;
        isoTime -= hour * 100'00'000;
        int minute = isoTime / 100'000;
        isoTime -= minute * 100'000;
        int second = isoTime / 1000;
        isoTime -= second * 1000;
        int millisecond = isoTime;

        // Create local_date_time object
        return dot::local_date_time(year, month, day, hour, minute, second, millisecond);
    }

    std::chrono::milliseconds local_date_time_util::ToStdChrono(dot::local_date_time value)
    {
        boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::date_time::Jan, 1));
        boost::posix_time::time_duration d = (boost::posix_time::ptime)value - epoch;
        return std::chrono::milliseconds(d.total_milliseconds());
    }

    dot::local_date_time local_date_time_util::FromStdChrono(std::chrono::milliseconds value)
    {
        boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::date_time::Jan, 1));
        boost::posix_time::time_duration d = boost::posix_time::milliseconds(value.count());
        return epoch + d;
    }
}