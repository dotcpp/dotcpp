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

namespace cl
{
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
        IList<double> b = a;

        b->Add(0.0);
        b->Add(1.0);
        b->Add(2.0);

        BOOST_CHECK(a->getCount() == 3);
        BOOST_CHECK(b->getCount() == 3);
    }

    test_suite* ListTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("ListTest");
        suite->add(BOOST_TEST_CASE(&ListTest::Smoke));
        suite->add(BOOST_TEST_CASE(&ListTest::Interfaces));
        return suite;
    }
}
