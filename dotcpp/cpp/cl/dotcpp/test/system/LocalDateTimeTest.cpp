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

#include <cl/dotcpp/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Period.hpp>
#include <cl/dotcpp/main/system/LocalTime.hpp>
#include <cl/dotcpp/main/system/LocalDate.hpp>
#include <cl/dotcpp/main/system/LocalDateTime.hpp>

namespace cl
{
    TEST_CASE("Properties")
    {
        LocalDateTime d(2005, 1, 10, 12, 10, 20, 30);
        REQUIRE((LocalDate)d.Date == LocalDate(2005, 1, 10));
        REQUIRE(d.Year == 2005);
        REQUIRE(d.Month == 1);
        REQUIRE(d.Day == 10);
        REQUIRE(d.DayOfWeek == boost::gregorian::Monday);
        REQUIRE(d.DayOfYear == 10);
        REQUIRE((LocalTime)d.TimeOfDay == LocalTime(12, 10, 20, 30));
        REQUIRE(d.Hour == 12);
        REQUIRE(d.Minute == 10);
        REQUIRE(d.Second == 20);
        REQUIRE(d.Millisecond == 30);
    }

    TEST_CASE("Methods")
    {
        LocalDateTime d(2005, 1, 10, 12, 10, 20, 30);
        REQUIRE(d.PlusDays(10) == LocalDateTime(2005, 1, 20, 12, 10, 20, 30));
        REQUIRE(d.PlusWeeks(1) == LocalDateTime(2005, 1, 17, 12, 10, 20, 30));
        REQUIRE(d.PlusMonths(1) == LocalDateTime(2005, 2, 10, 12, 10, 20, 30));
        REQUIRE(d.PlusYears(1) == LocalDateTime(2006, 1, 10, 12, 10, 20, 30));
        REQUIRE(d.PlusHours(1) == LocalDateTime(2005, 1, 10, 13, 10, 20, 30));
        REQUIRE(d.PlusMinutes(1) == LocalDateTime(2005, 1, 10, 12, 11, 20, 30));
        REQUIRE(d.PlusSeconds(1) == LocalDateTime(2005, 1, 10, 12, 10, 21, 30));
        REQUIRE(d.PlusMilliseconds(1) == LocalDateTime(2005, 1, 10, 12, 10, 20, 31));

        LocalDateTime d2(2005, 1, 10, 12, 10);
        REQUIRE(d2.Previous(boost::gregorian::Monday) == LocalDateTime(2005, 1, 3, 12, 10));
        REQUIRE(d2.Next(boost::gregorian::Monday) == LocalDateTime(2005, 1, 17, 12, 10));
    }

    TEST_CASE("Operators")
    {
        LocalDateTime d(2005, 5, 10, 12, 0, 0, 0);
        LocalDateTime d1(2005, 5, 10, 12, 0, 0, 0);
        LocalDateTime d2(2005, 5, 15, 13, 1, 1, 1);
        LocalDateTime d3(2005, 5, 20, 14, 2, 2, 2);

        Period p1 = Period::Between(d1, d2);
        Period p2 = Period::Between(d2, d3);
        Period p3 = Period::Between(d1, d3);

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
