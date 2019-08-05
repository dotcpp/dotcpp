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

#include <dot/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <dot/system/string.hpp>
#include <dot/noda_time/period.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/local_date.hpp>
#include <dot/noda_time/local_date_time.hpp>

namespace dot
{
    TEST_CASE("Constructors")
    {
        local_date_time defaultConstructed;
        local_date_time janOneYearOneConstructed(1970, 1, 1, 0, 0, 0);
        REQUIRE(defaultConstructed == janOneYearOneConstructed);
    }

    TEST_CASE("Properties")
    {
        local_date_time d(2005, 1, 10, 12, 10, 20, 30);
        REQUIRE((local_date)d.date() == local_date(2005, 1, 10));
        REQUIRE(d.year() == 2005);
        REQUIRE(d.month() == 1);
        REQUIRE(d.day() == 10);
        REQUIRE(d.day_of_week() == boost::gregorian::Monday);
        REQUIRE(d.day_of_year() == 10);
        REQUIRE((local_time)d.time_of_day() == local_time(12, 10, 20, 30));
        REQUIRE(d.hour() == 12);
        REQUIRE(d.minute() == 10);
        REQUIRE(d.second() == 20);
        REQUIRE(d.millisecond() == 30);
    }

    TEST_CASE("Methods")
    {
        local_date_time dt1(2005, 1, 10, 12, 10, 20, 30);
        REQUIRE(dt1.PlusDays(10) == local_date_time(2005, 1, 20, 12, 10, 20, 30));
        REQUIRE(dt1.PlusWeeks(1) == local_date_time(2005, 1, 17, 12, 10, 20, 30));
        REQUIRE(dt1.PlusMonths(1) == local_date_time(2005, 2, 10, 12, 10, 20, 30));
        REQUIRE(dt1.PlusYears(1) == local_date_time(2006, 1, 10, 12, 10, 20, 30));
        REQUIRE(dt1.PlusHours(1) == local_date_time(2005, 1, 10, 13, 10, 20, 30));
        REQUIRE(dt1.PlusMinutes(1) == local_date_time(2005, 1, 10, 12, 11, 20, 30));
        REQUIRE(dt1.PlusSeconds(1) == local_date_time(2005, 1, 10, 12, 10, 21, 30));
        REQUIRE(dt1.PlusMilliseconds(1) == local_date_time(2005, 1, 10, 12, 10, 20, 31));

        local_date_time dt2(2005, 1, 10, 12, 10);
        REQUIRE(dt2.Previous(boost::gregorian::Monday) == local_date_time(2005, 1, 3, 12, 10));
        REQUIRE(dt2.Next(boost::gregorian::Monday) == local_date_time(2005, 1, 17, 12, 10));

        local_date_time dt3(2005, 1, 2, 3, 4, 5, 6);
        string dt3_str = dt3.to_string();
        REQUIRE(dt3_str == "2005-01-02 03:04:05.006");
    }

    TEST_CASE("Operators")
    {
        local_date_time d(2005, 5, 10, 12, 0, 0, 0);
        local_date_time d1(2005, 5, 10, 12, 0, 0, 0);
        local_date_time d2(2005, 5, 15, 13, 1, 1, 1);
        local_date_time d3(2005, 5, 20, 14, 2, 2, 2);

        period p1 = period::between(d1, d2);
        period p2 = period::between(d2, d3);

        REQUIRE(d2 + p1 == d3);
        REQUIRE(d2 - d1 == p2);
        REQUIRE(d3 - p2 == d2);

        REQUIRE(d1 == d);
        REQUIRE(d1 != d2);
        REQUIRE(d2 != d3);

        REQUIRE(d1 <= d1);
        REQUIRE(d1 <= d2);
        REQUIRE(d2 <= d3);

        REQUIRE(d1 < d2);
        REQUIRE(d1 < d3);
        REQUIRE(d2 < d3);

        REQUIRE(d1 >= d1);
        REQUIRE(d2 >= d1);
        REQUIRE(d3 >= d2);

        REQUIRE(d2 > d1);
        REQUIRE(d3 > d1);
        REQUIRE(d3 > d2);
    }
}
