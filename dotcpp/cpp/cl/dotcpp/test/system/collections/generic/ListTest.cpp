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
#include <cl/dotcpp/test/system/collections/generic/ListTest.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    void sortDoubleVector(std::vector<double>& v)
    {
        // Sort the argument std::vector<double>
        std::sort(v.begin(), v.end());
    }

    void ListTest::Smoke()
    {
        List<double> a = new_List<double>();
        a->Add(0.0);
        a->Add(1.0);
        a->Add(2.0);

        BOOST_CHECK(a->getCount() == 3);
    }

    void ListTest::Interfaces()
    {
        List<double> a = new_List<double>();

        // Add elements to IList interface
        IList<double> b = a;
        b->Add(2.0);
        b->Add(1.0);
        b->Add(0.0);

        // Check size of the original class and the interface
        BOOST_CHECK(a->getCount() == 3);
        BOOST_CHECK(b->getCount() == 3);

        // Access the underlying std::vector<double> class
        sortDoubleVector(*a);
        BOOST_CHECK(a[0] == 0.0);
    }

    void ListTest::Iterators()
    {
        List<String> stringList = new_List<String>();
        stringList->Add("000");
        stringList->Add("111");
        stringList->Add("222");
        BOOST_CHECK(stringList->getCount() == 3);

        int i = 0;
        for (String str : stringList)
        {
            BOOST_CHECK(stringList[i++] == str);
        }
    }

    void ListTest::Capacity()
    {
        List<String> stringList = new_List<String>();
        stringList->Capacity = 100;
        BOOST_CHECK(stringList->Capacity == 100);
        BOOST_CHECK(stringList->capacity() == 100);
    }

    void ListTest::Find()
    {
        cl::List<String> stringList = new_List<String>();
        stringList->Add("000");
        stringList->Add("111");
        stringList->Add("222");
        stringList->Add("333");
        stringList->Add("444");

        // TODO stringList.findLast([](std::string const& s) { return s == "222"; }) = "57";
        // TODO BOOST_CHECK(stringList.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
    }

    test_suite* ListTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("ListTest");
        suite->add(BOOST_TEST_CASE(&ListTest::Smoke));
        suite->add(BOOST_TEST_CASE(&ListTest::Interfaces));
        suite->add(BOOST_TEST_CASE(&ListTest::Iterators));
        suite->add(BOOST_TEST_CASE(&ListTest::Capacity));
        suite->add(BOOST_TEST_CASE(&ListTest::Find));
        return suite;
    }
}
