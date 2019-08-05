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
        local_time defaultConstructed;
        local_time janOneYearOneConstructed(0, 0, 0);
        REQUIRE(defaultConstructed == janOneYearOneConstructed);
    }

    TEST_CASE("Properties")
    {
        local_time t(12, 10, 20, 30);
        REQUIRE(t.hour() == 12);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.second() == 20);
        REQUIRE(t.millisecond() == 30);
    }

    TEST_CASE("Methods")
    {
        local_time t1(12, 10, 20, 30);
        REQUIRE(t1.PlusHours(1) == local_time(13, 10, 20, 30));
        REQUIRE(t1.PlusMinutes(1) == local_time(12, 11, 20, 30));
        REQUIRE(t1.PlusSeconds(1) == local_time(12, 10, 21, 30));
        REQUIRE(t1.PlusMilliseconds(1) == local_time(12, 10, 20, 31));

        local_time t2(23, 59);
        REQUIRE(t2.PlusHours(2) == local_time(1, 59));
        REQUIRE(t2.PlusMinutes(2) == local_time(0, 1));

        local_date_time dt3(2005, 5, 10, 12, 10);
        local_date d3(2005, 5, 10);
        local_time t3(12, 10);
        REQUIRE(t3.On(d3) == dt3);

        local_time t4(1, 2, 3, 4);
        string t4_str = t4.to_string();
        REQUIRE(t4_str == "01:02:03.004");
    }

    TEST_CASE("Operators")
    {
        local_time t(12, 0, 0, 0);
        local_time t1(12, 0, 0, 0);
        local_time t2(13, 1, 1, 1);
        local_time t3(14, 2, 2, 2);
        period p1 = period::between(t1, t2);
        period p2 = period::between(t2, t3);

        REQUIRE(t2 + p1 == t3);
        REQUIRE(t2 - t1 == p2);
        REQUIRE(t3 - p2 == t2);

        REQUIRE(t1 == t);
        REQUIRE(t1 != t2);
        REQUIRE(t2 != t3);

        REQUIRE(t1 <= t1);
        REQUIRE(t1 <= t2);
        REQUIRE(t2 <= t3);

        REQUIRE(t1 < t2);
        REQUIRE(t1 < t3);
        REQUIRE(t2 < t3);

        REQUIRE(t1 >= t1);
        REQUIRE(t2 >= t1);
        REQUIRE(t3 >= t2);

        REQUIRE(t2 > t1);
        REQUIRE(t3 > t1);
        REQUIRE(t3 > t2);
    }
}
