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
#include <cl/dotcpp/test/system/Array1DTest.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    /// <summary>Smoke test.</summary>
    void Array1DTest::Smoke()
    {
        Array1D<double> stringArray = new_Array1D<double>(3);
        stringArray[0] = 0.0;
        stringArray[1] = 1.0;
        stringArray[2] = 2.0;

        BOOST_CHECK(stringArray->getCount() == 3);
    }

    /// <summary>Test interfaces.</summary>
    void Array1DTest::Interfaces()
    {
        Array1D<double> a = new_Array1D<double>(3);
        IList<double> b = a;
 
        // Check size of the original class and the interface
        BOOST_CHECK(a->getCount() == 3);
        BOOST_CHECK(b->getCount() == 3);

        // Access the underlying std::vector<double> class
        SortDoubleVector(*a);
        BOOST_CHECK(b[0] == 0.0);

        // Access by Object
        Object obj = b;
        BOOST_CHECK(obj->ToString() == "Object");

        // Check that methods that should throw actually throw
        BOOST_CHECK_THROW(b->Add(0.0), Exception);
        BOOST_CHECK_THROW(b->Clear(), Exception);
    }

    /// <summary>Test iterators.</summary>
    void Array1DTest::Iterators()
    {
        Array1D<String> stringArray = new_Array1D<String>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        BOOST_CHECK(stringArray->getCount() == 3);
        BOOST_CHECK(stringArray[2] == "222");

        int i = 0;
        for (String str : stringArray)
        {
            BOOST_CHECK(stringArray[i++] == str);
        }
    }

    /// <summary>Test capacity.</summary>
    void Array1DTest::Capacity()
    {
        Array1D<String> stringArray = new_Array1D<String>(0);
        stringArray->Capacity = 100;
        BOOST_CHECK(stringArray->Capacity == 100);
        BOOST_CHECK(stringArray->capacity() == 100);
    }

    /// <summary>Test find methods.</summary>
    void Array1DTest::Find()
    {
        cl::Array1D<String> stringArray = new_Array1D<String>(5);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";

        // TODO stringArray.findLast([](std::string const& s) { return s == "222"; }) = "57";
        // TODO BOOST_CHECK(stringArray.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
    }

    /// <summary>Test enumerator methods.</summary>
    void Array1DTest::Enumerator()
    {
        cl::Array1D<String> stringArray = new_Array1D<String>(3);
        stringArray[0] = "000";
        stringArray[1] = "111";
        stringArray[2] = "222";
        BOOST_CHECK(stringArray->getCount() == 3);

        int i = 0;

        for (String str : stringArray)
        {
            BOOST_CHECK((stringArray.as<Array1D<String>>())[i++] == str);
        }

        i = 0;
        IEnumerator<String> en = stringArray->GetEnumerator();

        for (; en->MoveNext();)
        {
            BOOST_CHECK((stringArray.as<Array1D<String>>())[i++] == en->getCurrent());

        }

        i = 0;
        en->Reset();

        for (; en->MoveNext();)
        {
            BOOST_CHECK((stringArray.as<Array1D<String>>())[i++] == en->getCurrent());

        }
    }

    test_suite* Array1DTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("Array1DTest");
        suite->add(BOOST_TEST_CASE(&Array1DTest::Smoke));
        suite->add(BOOST_TEST_CASE(&Array1DTest::Interfaces));
        suite->add(BOOST_TEST_CASE(&Array1DTest::Iterators));
        suite->add(BOOST_TEST_CASE(&Array1DTest::Capacity));
        suite->add(BOOST_TEST_CASE(&Array1DTest::Find));
        suite->add(BOOST_TEST_CASE(&Array1DTest::Enumerator));
        return suite;
    }
}
