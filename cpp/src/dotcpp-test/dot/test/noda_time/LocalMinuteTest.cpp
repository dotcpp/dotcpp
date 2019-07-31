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
#include <dot/noda_time/LocalMinute.hpp>
#include <dot/noda_time/LocalTime.hpp>

namespace dot
{
    TEST_CASE("Properties")
    {
        local_minute t(12, 10);
        REQUIRE(t.hour() == 12);
        REQUIRE(t.minute() == 10);
        REQUIRE(t.minute_of_day() == 730);
    }

    TEST_CASE("Methods")
    {
        local_minute localMinute(12, 10);
        local_minute localMinute2(12, 10);
        local_minute localMinuteAfter(13, 20);
        local_minute localMinuteBefore(11, 0);

        LocalTime localTime(12, 10);
        REQUIRE(localMinute.to_local_time() == localTime);
        REQUIRE(localMinute.to_string() == "12:10");

        REQUIRE(localMinute.compare_to(localMinute2) == 0);
        REQUIRE(localMinute.compare_to(localMinuteAfter) == -1);
        REQUIRE(localMinute.compare_to(localMinuteBefore) == 1);

        REQUIRE(localMinute.hash_code() == localMinute2.hash_code());
        REQUIRE(localMinute.hash_code() != localMinuteBefore.hash_code());
        REQUIRE(localMinute.hash_code() != localMinuteAfter.hash_code());

        REQUIRE(localMinute.equals(localMinute2) == true);
        REQUIRE(localMinute.equals(localMinuteAfter) == false);
        REQUIRE(localMinute.equals(localMinuteBefore) == false);
    }

    TEST_CASE("Operators")
    {
        local_minute t(12, 0);
        local_minute t1(12, 0);
        local_minute t2(13, 1);
        local_minute t3(14, 2);

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
