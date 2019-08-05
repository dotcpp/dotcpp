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
#include <dot/system/array.hpp>
#include <dot/system/object.hpp>

namespace dot
{
    /// <summary>Sort vector in ascending order.</summary>
    static void SortDoubleVector(std::vector<double>& v)
    {
        // Sort the argument std::vector<double>
        std::sort(v.begin(), v.end());
    }

    TEST_CASE("Smoke")
    {
        array<double> stringArray = make_array<double>(3);
        stringArray[0] = 0.0;
        stringArray[1] = 1.0;
        stringArray[2] = 2.0;

        REQUIRE(stringArray->count() == 3);
    }

    TEST_CASE("Methods")
    {
        array<double> a = make_array<double>(3);
 
        // Check size of the original class and the interface
        REQUIRE(a->count() == 3);

        // Access the underlying std::vector<double> class
        SortDoubleVector(*a);
        REQUIRE(a[0] == 0.0);

        // Access by object
        object obj = a;
        REQUIRE(((array<double>)obj)->count() == 3);

        // Check that methods that should throw actually throw
        // CHECK_THROWS_AS(b->Add(0.0), Exception);
        // CHECK_THROWS_AS(b->Clear(), Exception);
    }

    TEST_CASE("Iterators")
    {
        array<string> stringArray = make_array<string>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        REQUIRE(stringArray->count() == 3);
        REQUIRE(stringArray[2] == "222");

        int i = 0;
        for (string str : stringArray)
        {
            REQUIRE(stringArray[i++] == str);
        }
    }

    TEST_CASE("Find")
    {
        dot::array<string> stringArray = make_array<string>(5);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";

        // TODO stringArray.findLast([](std::string const& s) { return s == "222"; }) = "57";
        // TODO REQUIRE(stringArray.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
    }

    TEST_CASE("Enumerator")
    {
        dot::array<string> stringArray = make_array<string>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        REQUIRE(stringArray->count() == 3);

        int i = 0;

        for (string str : stringArray)
        {
            REQUIRE((stringArray.as<array<string>>())[i++] == str);
        }
    }

    TEST_CASE("to_string")
    {
        array<double> obj = make_array<double>(3);
        auto type = obj->type();
        string fullname = type->full_name();

        REQUIRE(type->to_string() == "System.Double[]");
    }
}
