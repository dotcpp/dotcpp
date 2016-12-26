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

#ifndef __cl_system_collections_generic_CppListTests_hpp__
#define __cl_system_collections_generic_CppListTests_hpp__

#include <cl/system/collections/generic/CppList.hpp>
#include <cl/system/collections/generic/CppDictionary.hpp>

namespace std {
    ::std::ostream& operator << (::std::ostream& stg, std::string const& s)  {
        stg << s.c_str();
        return stg;
    }
}

namespace cl {
    typedef std::string String;
}

BOOST_AUTO_TEST_SUITE(CppListTests)

BOOST_AUTO_TEST_CASE(iteration)
{
    cl::Dictionary<std::string, int> dictionary;

    cl::List<cl::String> stringList;
    stringList.Add("111");
    stringList.Add("222");
    stringList.Add("333");
    BOOST_REQUIRE_EQUAL(stringList.get_Count(), 3);
    for each (cl::String str in stringList)
    {
        std::cout << str << " ";
    }

    std::string& ss =
        stringList.FindLast([](std::string const& s)
    {
        return s == "222";
    });

    const_cast<std::string& >(ss) = "57";
}

BOOST_AUTO_TEST_CASE(FindLast)
{
    cl::List<cl::String> stringList;
    stringList.Add("111");
    stringList.Add("222");
    stringList.Add("222");
    stringList.Add("222");
    stringList.Add("333");
    BOOST_REQUIRE_EQUAL(stringList.get_Count(), 5);

    stringList.FindLast([](std::string const& s){ return s == "222"; }) = "57";

    BOOST_REQUIRE_EQUAL(stringList[3], "57");
}

BOOST_AUTO_TEST_CASE(FindLastIndex)
{
    cl::List<cl::String> stringList;
    stringList.Add("111");
    stringList.Add("222");
    stringList.Add("222");
    stringList.Add("333");
    BOOST_REQUIRE_EQUAL(stringList.get_Count(), 4);

    BOOST_REQUIRE_EQUAL(stringList.FindLastIndex([](std::string const& s){ return s == "222"; }), 2);
}

BOOST_AUTO_TEST_SUITE_END()

#endif // __cl_system_collections_generic_CppListTests_hpp__
