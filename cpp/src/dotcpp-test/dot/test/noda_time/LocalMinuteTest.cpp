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
#include <dot/nodatime/LocalMinute.hpp>
#include <dot/nodatime/LocalTime.hpp>

namespace dot
{
    TEST_CASE("Properties")
    {
        LocalMinute t(12, 10);
        REQUIRE(t.Hour == 12);
        REQUIRE(t.Minute == 10);
        REQUIRE(t.MinuteOfDay == 730);
    }

    TEST_CASE("Methods")
    {
        LocalMinute localMinute(12, 10);
        LocalMinute localMinute2(12, 10);
        LocalMinute localMinuteAfter(13, 20);
        LocalMinute localMinuteBefore(11, 0);

        LocalTime localTime(12, 10);
        REQUIRE(localMinute.ToLocalTime() == localTime);

        REQUIRE(localMinute.CompareTo(localMinute2) == 0);
        REQUIRE(localMinute.CompareTo(localMinuteAfter) == -1);
        REQUIRE(localMinute.CompareTo(localMinuteBefore) == 1);

        REQUIRE(localMinute.GetHashCode() == localMinute2.GetHashCode());
        REQUIRE(localMinute.GetHashCode() != localMinuteBefore.GetHashCode());
        REQUIRE(localMinute.GetHashCode() != localMinuteAfter.GetHashCode());

        REQUIRE(localMinute.Equals(localMinute2) == true);
        REQUIRE(localMinute.Equals(localMinuteAfter) == false);
        REQUIRE(localMinute.Equals(localMinuteBefore) == false);

        LocalMinute localMinuteStr(1, 0);
        REQUIRE(localMinuteStr.ToIsoInt() == 100);
        REQUIRE(localMinuteStr.ToIsoString() == "01:00");
    }

    TEST_CASE("Operators")
    {
        LocalMinute t(12, 0);
        LocalMinute t1(12, 0);
        LocalMinute t2(13, 1);
        LocalMinute t3(14, 2);

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
