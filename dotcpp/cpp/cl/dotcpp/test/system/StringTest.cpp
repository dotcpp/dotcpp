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
#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    TEST_CASE("Smoke")
    {
        // Create from std::string
        String s1 = std::string("abc");
        REQUIRE(s1 == "abc");
        REQUIRE(s1 == std::string("abc"));

        // Create from string literal
        String s2 = "abc";
        REQUIRE(s2 == "abc");

        // Cast to Object and back
        Object obj1 = s1;
        // TODO String s11 = obj1.cast<String>();
        // TODO  REQUIRE(s11 == "abc");
    }

    TEST_CASE("Format")
    {
        REQUIRE(String::Format("{0}", 1) == "1");
        REQUIRE(String::Format("1") == "1");
    }

    TEST_CASE("Compare")
    {
        // Compare to literal strings
        String str = "abcd";
        REQUIRE(str == "abcd");

        // Check comparison case sensitivity
        REQUIRE_FALSE(str == "Abcd");

        // Compare two strings that have the same value but are not the same instances
        String str2 = "abcd";
        REQUIRE(str == str2);

        // Compare two strings that have the same value but are not
        // the same instances after casting one or both to object
        REQUIRE(str == (Object)str2);
        // TODO - fix by implemnenting Equals(...) REQUIRE((Object)str == str2);
        // TODO - fix by implemnenting Equals(...) REQUIRE((Object)str == (Object)str2);
    }
}
