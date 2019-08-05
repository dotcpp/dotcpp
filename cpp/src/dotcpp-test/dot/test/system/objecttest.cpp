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

namespace dot
{
    TEST_CASE("Clear object")
    {
        object a = new_object();
        object b = new_object();

        REQUIRE(a->equals(a) == true);
        REQUIRE(a->equals(b) == false);
        REQUIRE(a->hash_code() != b->hash_code());
    }

    TEST_CASE("Equals")
    {
        object a = make_string("str");
        object b = make_string("str");
        object c = make_string("str1");

        REQUIRE(a->equals(a));
        REQUIRE(a->equals(b));
        REQUIRE(a->equals(c) == false);

        REQUIRE(a->hash_code() == a->hash_code());
        REQUIRE(a->hash_code() == b->hash_code());
        REQUIRE(a->hash_code() != c->hash_code());
    }
}
