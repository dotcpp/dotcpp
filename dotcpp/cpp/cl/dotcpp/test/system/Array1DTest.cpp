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
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    /// <summary>Sort vector in ascending order.</summary>
    static void SortDoubleVector(std::vector<double>& v)
    {
        // Sort the argument std::vector<double>
        std::sort(v.begin(), v.end());
    }

    TEST_CASE("Smoke")
    {
        Array1D<double> stringArray = new_Array1D<double>(3);
        stringArray[0] = 0.0;
        stringArray[1] = 1.0;
        stringArray[2] = 2.0;

        REQUIRE(stringArray->Count == 3);
    }

    TEST_CASE("Interfaces")
    {
        Array1D<double> a = new_Array1D<double>(3);
        Array b = a;
 
        // Check size of the original class and the interface
        REQUIRE(a->Count == 3);
        REQUIRE(b->Count == 3);

        // Access the underlying std::vector<double> class
        SortDoubleVector(*a);
        REQUIRE(a[0] == 0.0);

        // Access by Object
        Object obj = b;
        REQUIRE(((Array1D<double>)b)->Count == 3);

        // Check that methods that should throw actually throw
        // CHECK_THROWS_AS(b->Add(0.0), Exception);
        // CHECK_THROWS_AS(b->Clear(), Exception);
    }

    TEST_CASE("Iterators")
    {
        Array1D<String> stringArray = new_Array1D<String>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        REQUIRE(stringArray->Count == 3);
        REQUIRE(stringArray[2] == "222");

        int i = 0;
        for (String str : stringArray)
        {
            REQUIRE(stringArray[i++] == str);
        }
    }

    TEST_CASE("Find")
    {
        cl::Array1D<String> stringArray = new_Array1D<String>(5);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";

        // TODO stringArray.findLast([](std::string const& s) { return s == "222"; }) = "57";
        // TODO REQUIRE(stringArray.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
    }

    TEST_CASE("Enumerator")
    {
        cl::Array1D<String> stringArray = new_Array1D<String>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        REQUIRE(stringArray->Count == 3);

        int i = 0;

        for (String str : stringArray)
        {
            REQUIRE((stringArray.as<Array1D<String>>())[i++] == str);
        }
    }

    TEST_CASE("ToString")
    {
        Array1D<double> obj = new_Array1D<double>(3);
        auto type = obj->GetType();
        String fullname = type->FullName;

        REQUIRE(type->ToString() == "System.T[]"); // TODO provide custom logic to resolve T[] into specific name
    }
}
