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
#include <dot/system/collections/generic/IEnumerable.hpp>
#include <dot/system/Array1D.hpp>
#include <dot/system/collections/generic/List.hpp>
#include <dot/system/String.hpp>
#include <dot/system/Type.hpp>

namespace dot
{
    static std::stringstream received;

    /// <summary>Print double vector to received on one line in JSON format.</summary>
    static void PrintList(String name, List<double> v)
    {
        received << "\"" << *name << "\" : [ ";
        for (int i = 0; i < v->Count; ++i)
        {
            if (i > 0) received << ", ";
            received << v[i];
        }
        received << " ]" << std::endl;
    }

    TEST_CASE("Smoke")
    {
        List<double> a = new_List<double>();
        a->Add(0.0);
        a->Add(1.0);
        a->Add(2.0);

        REQUIRE(a->Count == 3);

        auto b = a->ToArray();
        REQUIRE(b->Count == 3);
        REQUIRE(b[2] == 2.0);
    }

    TEST_CASE("Interfaces")
    {
        List<double> a = new_List<double>();

        // Add elements to IList interface
        IList<double> b = a;
        b->Add(2.0);
        b->Add(1.0);
        b->Add(0.0);

        // Check size of the original class and the interface
        REQUIRE(a->Count == 3);
        REQUIRE(b->Count == 3);

        // Access the underlying std::vector<double> class
        PrintList("Unsorted", a);
        std::sort(a->begin(), a->end());
        PrintList("Sorted", a);

        // Access by Object
        Object obj = b;
        // TODO - uncomment next line when output matches C#
        // received << obj->ToString() << std::endl;

        Approvals::verify(received.str());
        received.clear();
    }

    TEST_CASE("Iterators")
    {
        List<String> stringList = new_List<String>();
        stringList->Add("000");
        stringList->Add("111");
        stringList->Add("222");
        REQUIRE(stringList->Count == 3);

        int i = 0;
        for (String str : stringList)
        {
            REQUIRE(stringList[i++] == str);
        }
    }

    TEST_CASE("Capacity")
    {
        List<String> stringList = new_List<String>();
        stringList->Capacity = 100;
        REQUIRE(stringList->Capacity == 100);
        REQUIRE(stringList->capacity() == 100);
    }

    TEST_CASE("Find")
    {
        dot::List<String> stringList = new_List<String>();
        stringList->Add("000");
        stringList->Add("111");
        stringList->Add("222");
        stringList->Add("333");
        stringList->Add("444");

        // TODO stringList.findLast([](std::string const& s) { return s == "222"; }) = "57";
        // TODO REQUIRE(stringList.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
    }

    TEST_CASE("Enumerator")
    {
        // Create list
        List<String> stringList = new_List<String>();
        stringList->Add("000");
        stringList->Add("111");
        stringList->Add("222");
        REQUIRE(stringList->Count == 3);

        // Iterate using foreach
        int i = 0;
        for (String str : stringList)
        {
            REQUIRE(stringList[i++] == str);
        }

        i = 0;
        for (String str : stringList.as<IEnumerable<String>>())
        {
            REQUIRE(stringList[i++] == str);
        }

        // Iterate using enumerator
        i = 0;
        IEnumerator<String> en = stringList->GetEnumerator();

        for (; en->MoveNext();)
        {
            REQUIRE(stringList[i++] == en->getCurrent());
        }

        // Reset the enumerator and iterate again
        i = 0;
        en->Reset();
        for (; en->MoveNext();)
        {
            REQUIRE(stringList[i++] == en->getCurrent());
        }
    }
}
