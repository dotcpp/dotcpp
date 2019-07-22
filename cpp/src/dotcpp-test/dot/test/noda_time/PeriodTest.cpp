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

#include <dot/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <dot/system/String.hpp>
#include <dot/nodatime/Period.hpp>
#include <dot/nodatime/LocalTime.hpp>
#include <dot/nodatime/LocalDate.hpp>
#include <dot/nodatime/LocalDateTime.hpp>

namespace dot
{
    TEST_CASE("Create")
    {
        {
            LocalDateTime date1(2005, 1, 1, 0, 0);
            LocalDateTime date2(2006, 1, 1, 0, 0);

            Period p = Period::Between(date1, date2);
            REQUIRE(p.Days == 365);
        }

        {
            LocalDateTime date1(2005, 1, 1, 1, 11, 11, 111);
            LocalDateTime date2(2005, 1, 10, 2, 22, 22, 222);
            Period p = Period::Between(date1, date2);
            REQUIRE(p.Days == 9);
            REQUIRE(p.Hours == 1);
            REQUIRE(p.Minutes == 11);
            REQUIRE(p.Seconds == 11);
            REQUIRE(p.Milliseconds == 111);
        }

        {
            LocalDate date1(2005, 1, 1);
            LocalDate date2(2005, 1, 10);
            Period p = Period::Between(date1, date2);
            REQUIRE(p.Days == 9);
            REQUIRE(p.Hours == 0);
            REQUIRE(p.Minutes == 0);
            REQUIRE(p.Seconds == 0);
            REQUIRE(p.Milliseconds == 0);
        }

        {
            LocalTime time1(1, 11, 11, 111);
            LocalTime time2(2, 22, 22, 222);
            Period p = Period::Between(time2, time1);
            REQUIRE(p.Days == 0);
            REQUIRE(p.Hours == -1);
            REQUIRE(p.Minutes == -11);
            REQUIRE(p.Seconds == -11);
            REQUIRE(p.Milliseconds == -111);
        }

        {
            Period p = Period::FromWeeks(1);
            REQUIRE(p.Days == 7);

            p = Period::FromDays(1);
            REQUIRE(p.Days == 1);

            p = Period::FromHours(1);
            REQUIRE(p.Hours == 1);

            p = Period::FromMinutes(1);
            REQUIRE(p.Minutes == 1);

            p = Period::FromSeconds(1);
            REQUIRE(p.Seconds == 1);

            p = Period::FromMilliseconds(1);
            REQUIRE(p.Milliseconds == 1);
        }
    }

    TEST_CASE("Methods")
    {
        LocalDateTime date1(2005, 1, 1, 0, 0, 0, 0);
        LocalDateTime date2(2005, 1, 2, 1, 1, 1, 1);
        LocalDateTime date3(2005, 1, 3, 2, 2, 2, 2);
        Period p1 = Period::Between(date1, date2);
        Period p2 = Period::Between(date2, date3);
        Period p3 = Period::Between(date1, date3);

        REQUIRE(p1 == p2);
        REQUIRE(p1 + p2 == p3);
        REQUIRE(p3 - p2 == p1);
        REQUIRE(p3 - p1 == p2);
    }
}
