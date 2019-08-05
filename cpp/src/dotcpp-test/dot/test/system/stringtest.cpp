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
#include <dot/system/object.hpp>

namespace dot
{
    TEST_CASE("Smoke")
    {
        // Create from std::string
        string s1 = std::string("abc");
        REQUIRE(s1 == "abc");
        REQUIRE(s1 == std::string("abc"));

        // Create from string literal
        string s2 = "abc";
        REQUIRE(s2 == "abc");

        // Cast to object and back
        object obj1 = s1;
        // TODO string s11 = obj1.cast<string>();
        // TODO  REQUIRE(s11 == "abc");
    }

    TEST_CASE("Format")
    {
        int x = 1;
        double y = 2.5;
        const string s = "{0}";

        REQUIRE(string::format(s, x) == "1");
        REQUIRE(string::format("{0:.3f}", y) == "2.500");
        REQUIRE(string::format(s, s) == "{0}");
        REQUIRE(string::format("{0}, {1}", s, s) == "{0}, {0}");

        REQUIRE(string::format(string("{0}, {1}, {2}"), 1, "str1", string("str2")) == "1, str1, str2");
        REQUIRE(string::format("123") == "123");
        
        REQUIRE(string::format("{0}, {1}, {2}", 'a', 'b', 'c') == "a, b, c");
        REQUIRE(string::format("{}, {}, {}", 'a', 'b', 'c') == "a, b, c");
        REQUIRE(string::format("{2}, {1}, {0}", 'a', 'b', 'c') == "c, b, a");
        REQUIRE(string::format("{0}{1}{0}", "abra", "cad") == "abracadabra");
        
        REQUIRE(string::format("{:<15}", "left aligned") == "left aligned   ");
        REQUIRE(string::format("{:>15}", "right aligned") == "  right aligned");
        REQUIRE(string::format("{:^16}", "centered") == "    centered    ");
        REQUIRE(string::format("{:*^16}", "centered") == "****centered****");
        REQUIRE(string::format("{:<{}}", "left aligned", 15) == "left aligned   ");

        REQUIRE(string::format("{:.{}f}", 3.14, 1) == "3.1");
        REQUIRE(string::format("{:+f}; {:+f}", 3.14, -3.14) == "+3.140000; -3.140000");
        REQUIRE(string::format("{: f}; {: f}", 3.14, -3.14) == " 3.140000; -3.140000");
        REQUIRE(string::format("{:-f}; {:-f}", 3.14, -3.14) == "3.140000; -3.140000");

        REQUIRE(string::format("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42) == "int: 42;  hex: 2a;  oct: 52; bin: 101010");
        REQUIRE(string::format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42) == "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010");
        REQUIRE(string::format("{:#04x}", 0) == "0x00");
    }

    TEST_CASE("Compare")
    {
        // Compare to literal strings
        string str = "abcd";
        REQUIRE(str == "abcd");

        // Check comparison case sensitivity
        REQUIRE_FALSE(str == "Abcd");

        // Compare two strings that have the same value but are not the same instances
        string str2 = "abcd";
        REQUIRE(str == str2);

        // Compare two strings that have the same value but are not
        // the same instances after casting one or both to object
        REQUIRE(str == object(str2));
        // TODO - fix by implemnenting Equals(...) REQUIRE((object)str == str2);
        // TODO - fix by implemnenting Equals(...) REQUIRE((object)str == (object)str2);
    }
}
