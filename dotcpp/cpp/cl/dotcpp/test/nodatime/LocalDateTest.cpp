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
#include <cl/dotcpp/main/nodatime/Period.hpp>
#include <cl/dotcpp/main/nodatime/LocalTime.hpp>
#include <cl/dotcpp/main/nodatime/LocalDate.hpp>
#include <cl/dotcpp/main/nodatime/LocalDateTime.hpp>

namespace cl
{
    TEST_CASE("Constructors")
    {
        LocalDate defaultConstructed;
        LocalDate janOneYearOneConstructed(1970, 1, 1);
        REQUIRE(defaultConstructed == janOneYearOneConstructed);
    }

    TEST_CASE("Properties")
    {
        LocalDate d(2005, 1, 10);
        REQUIRE(d.Year == 2005);
        REQUIRE(d.Month == 1);
        REQUIRE(d.Day == 10);
        REQUIRE(d.DayOfWeek == boost::gregorian::Monday);
        REQUIRE(d.DayOfYear == 10);
    }

    TEST_CASE("Methods")
    {
        LocalDate d(2005, 1, 10);
        REQUIRE(d.PlusDays(10) == LocalDate(2005, 1, 20));
        REQUIRE(d.PlusWeeks(1) == LocalDate(2005, 1, 17));
        REQUIRE(d.PlusMonths(1) == LocalDate(2005, 2, 10));
        REQUIRE(d.PlusYears(1) == LocalDate(2006, 1, 10));

        LocalDate d2(2005, 1, 10);
        REQUIRE(d2.Previous(boost::gregorian::Monday) == LocalDate(2005, 1, 3));
        REQUIRE(d2.Next(boost::gregorian::Monday) == LocalDate(2005, 1, 17));

        LocalDateTime date_time(2005, 5, 10, 12, 10);
        LocalDate date(2005, 5, 10);
        LocalTime time(12, 10);
        REQUIRE(date.At(time) == date_time);
        REQUIRE(date.AtMidnight() == LocalDateTime(2005, 5, 10, 0, 0));

        LocalDate str_date(2005, 1, 2);
        REQUIRE(str_date.ToString() == "20050102");
    }

    TEST_CASE("Operators")
    {
        LocalDate d(2005, 5, 10);
        LocalDate d1(2005, 5, 10);
        LocalDate d2(2005, 5, 15);
        LocalDate d3(2005, 5, 20);

        Period p1 = Period::Between(d1, d2);
        Period p2 = Period::Between(d2, d3);

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
