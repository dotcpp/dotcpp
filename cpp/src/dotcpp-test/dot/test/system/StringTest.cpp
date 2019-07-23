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
#include <dot/system/String.hpp>
#include <dot/system/Object.hpp>

namespace dot
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
        int x = 1;
        double y = 2.5;
        const String s = "{0}";

        REQUIRE(String::Format(s, x) == "1");
        REQUIRE(String::Format("{0:.3f}", y) == "2.500");
        REQUIRE(String::Format(s, s) == "{0}");
        REQUIRE(String::Format("{0}, {1}", s, s) == "{0}, {0}");

        REQUIRE(String::Format(String("{0}, {1}, {2}"), 1, "str1", String("str2")) == "1, str1, str2");
        REQUIRE(String::Format("123") == "123");
        
        REQUIRE(String::Format("{0}, {1}, {2}", 'a', 'b', 'c') == "a, b, c");
        REQUIRE(String::Format("{}, {}, {}", 'a', 'b', 'c') == "a, b, c");
        REQUIRE(String::Format("{2}, {1}, {0}", 'a', 'b', 'c') == "c, b, a");
        REQUIRE(String::Format("{0}{1}{0}", "abra", "cad") == "abracadabra");
        
        REQUIRE(String::Format("{:<15}", "left aligned") == "left aligned   ");
        REQUIRE(String::Format("{:>15}", "right aligned") == "  right aligned");
        REQUIRE(String::Format("{:^16}", "centered") == "    centered    ");
        REQUIRE(String::Format("{:*^16}", "centered") == "****centered****");
        REQUIRE(String::Format("{:<{}}", "left aligned", 15) == "left aligned   ");

        REQUIRE(String::Format("{:.{}f}", 3.14, 1) == "3.1");
        REQUIRE(String::Format("{:+f}; {:+f}", 3.14, -3.14) == "+3.140000; -3.140000");
        REQUIRE(String::Format("{: f}; {: f}", 3.14, -3.14) == " 3.140000; -3.140000");
        REQUIRE(String::Format("{:-f}; {:-f}", 3.14, -3.14) == "3.140000; -3.140000");

        REQUIRE(String::Format("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42) == "int: 42;  hex: 2a;  oct: 52; bin: 101010");
        REQUIRE(String::Format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42) == "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010");
        REQUIRE(String::Format("{:#04x}", 0) == "0x00");
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
