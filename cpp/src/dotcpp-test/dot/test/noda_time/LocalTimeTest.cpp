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
#include <dot/noda_time/Period.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalDateTime.hpp>

namespace dot
{
    TEST_CASE("Constructors")
    {
        LocalTime defaultConstructed;
        LocalTime janOneYearOneConstructed(0, 0, 0);
        REQUIRE(defaultConstructed == janOneYearOneConstructed);
    }

    TEST_CASE("Properties")
    {
        LocalTime t(12, 10, 20, 30);
        REQUIRE(t.Hour == 12);
        REQUIRE(t.Minute == 10);
        REQUIRE(t.Second == 20);
        REQUIRE(t.Millisecond == 30);
    }

    TEST_CASE("Methods")
    {
        LocalTime t(12, 10, 20, 30);
        REQUIRE(t.PlusHours(1) == LocalTime(13, 10, 20, 30));
        REQUIRE(t.PlusMinutes(1) == LocalTime(12, 11, 20, 30));
        REQUIRE(t.PlusSeconds(1) == LocalTime(12, 10, 21, 30));
        REQUIRE(t.PlusMilliseconds(1) == LocalTime(12, 10, 20, 31));

        t = LocalTime(23, 59);
        REQUIRE(t.PlusHours(2) == LocalTime(1, 59));
        REQUIRE(t.PlusMinutes(2) == LocalTime(0, 1));

        LocalDateTime date_time(2005, 5, 10, 12, 10);
        LocalDate date(2005, 5, 10);
        LocalTime time(12, 10);
        REQUIRE(time.On(date) == date_time);

        LocalTime str_time(1, 2, 3, 4);
        REQUIRE(str_time.to_string() == "010203");
    }

    TEST_CASE("Operators")
    {
        LocalTime t(12, 0, 0, 0);
        LocalTime t1(12, 0, 0, 0);
        LocalTime t2(13, 1, 1, 1);
        LocalTime t3(14, 2, 2, 2);
        Period p1 = Period::Between(t1, t2);
        Period p2 = Period::Between(t2, t3);

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
