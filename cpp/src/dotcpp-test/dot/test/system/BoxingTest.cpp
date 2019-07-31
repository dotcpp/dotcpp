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
#include <dot/system/object.hpp>
#include <dot/system/string.hpp>
#include <dot/system/nullable.hpp>
#include <dot/system/collections/generic/list.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalDateTime.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    TEST_CASE("Smoke")
    {
        {
            // Boxing list of double
            list<double> obj = make_list<double>();
            obj->add(1.);
            obj->add(2.);
            obj->add(3.);

            object boxed = obj;
            list<double> unboxed = (list<double>)boxed;
            int i = 0;
            for (object item : unboxed)
            {
                REQUIRE((double)item == ++i);
            }
        }

        {
            // Boxing bool
            bool x = false;
            object boxed = x;
            REQUIRE((bool)boxed == false);
            boxed = true;
            REQUIRE((bool)boxed == true);
        }

        {
            // Boxing nullableBool
            nullable<bool> x;
            object boxed = x;
            REQUIRE(((nullable<bool>)boxed).has_value() == false);
            nullable<bool> y = true;
            boxed = y;
            REQUIRE((bool)boxed == true);
        }

        {
            // Boxing double
            double x = 1.0;
            object boxed = x;
            REQUIRE((double)boxed == 1.0);
            boxed = 2.0;
            REQUIRE((double)boxed == 2.0);
        }

        {
            // Boxing nullableDouble
            nullable<double> x;
            object boxed = x;
            REQUIRE(((nullable<double>)boxed).has_value() == false);
            nullable<double> y = 2.0;
            boxed = y;
            REQUIRE((double)boxed == 2.0);
        }

        {
            // Boxing int
            int x = 1;
            object boxed = x;
            REQUIRE((int)boxed == 1);
            boxed = 2;
            REQUIRE((int)boxed == 2);
        }

        {
            // Boxing nullableInt
            nullable<int> x;
            object boxed = x;
            REQUIRE(((nullable<int>)boxed).has_value() == false);
            nullable<int> y = 2;
            boxed = y;
            REQUIRE((int)boxed == 2);
        }

        {
            // Boxing int64_t
            int64_t x = 1;
            object boxed = x;
            REQUIRE((int64_t)boxed == 1);
            boxed = (int64_t)2;
            REQUIRE((int64_t)boxed == 2);
        }

        {
            // Boxing nullableLong
            nullable<int64_t> x;
            object boxed = x;
            REQUIRE(((nullable<int64_t>)boxed).has_value() == false);
            nullable<int64_t> y = (int64_t)2;
            boxed = y;
            REQUIRE((int64_t)boxed == 2);
        }

        {
            // Boxing local_time
            local_time time(12, 0);
            local_time time2(12, 0);

            object boxed = time;
            CHECK_NOTHROW((local_time) boxed);

            REQUIRE((local_time) boxed == time);
            REQUIRE((local_time) boxed == time2);
        }

        {
            // Boxing local_date
            local_date date(2005, 1, 1);
            local_date date2(2005, 1, 1);

            object boxed = date;
            CHECK_NOTHROW((local_date) boxed);

            REQUIRE((local_date) boxed == date);
            REQUIRE((local_date) boxed == date2);
        }

        {
            // Boxing local_date_time
            local_date_time date(2005, 1, 1, 12, 0);
            local_date_time date2(2005, 1, 1, 12, 0);

            object boxed = date;
            CHECK_NOTHROW((local_date_time) boxed);

            REQUIRE((local_date_time) boxed == date);
            REQUIRE((local_date_time) boxed == date2);
        }
    }
}