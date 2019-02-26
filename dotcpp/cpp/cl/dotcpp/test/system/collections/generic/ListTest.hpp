/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef cl_dotcpp_test_ListTests_hpp
#define cl_dotcpp_test_ListTests_hpp

#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/collections/generic/Dictionary.hpp>

namespace std {
    ::std::ostream& operator << (::std::ostream& stg, std::string const& s)  {
        stg << s.c_str();
        return stg;
    }
}

namespace cl {
    typedef std::string String; //!! Remove typedef and use the class directly
}

class CL_SYSTEM TListTests
{
public:

    static void iteration()
    {

        cl::TList<cl::String> stringList;
        stringList.add("111");
        stringList.add("222");
        stringList.add("333");
        BOOST_CHECK(stringList.count() == 3);

        for each (cl::String str in stringList)
        {
            std::cout << str << " ";
        }
        std::cout << std::endl;
        cl::String& ss =
            stringList.findLast([](std::string const& s)
        {
            return s == "222";
        });

        const_cast<cl::String& >(ss) = "57";

        BOOST_CHECK(stringList[1] == "57");
    }

    static void findLast()
    {
        cl::TList<cl::String> stringList;
        stringList.add("111");
        stringList.add("222");
        stringList.add("222");
        stringList.add("222");
        stringList.add("333");
        BOOST_CHECK(stringList.count() == 5);

        stringList.findLast([](std::string const& s){ return s == "222"; }) = "57";

        BOOST_CHECK(stringList[3] == "57");
    }

    static void findLastIndex()
    {
        cl::TList<cl::String> stringList;
        stringList.add("111");
        stringList.add("222");
        stringList.add("222");
        stringList.add("333");
        BOOST_CHECK(stringList.count() == 4);

        BOOST_CHECK(stringList.findLastIndex([](std::string const& s){ return s == "222"; }) == 2);
    }

    static test_suite* TListTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("TList test");
        suite->add(BOOST_TEST_CASE(&TListTests::iteration));
        suite->add(BOOST_TEST_CASE(&TListTests::findLast));
        suite->add(BOOST_TEST_CASE(&TListTests::findLastIndex));
        return suite;
    }
};

#endif // cl_dotcpp_test_ListTests_hpp
