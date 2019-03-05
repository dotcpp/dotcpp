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

#pragma once

#include <cl/dotcpp/test/declare.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <cl/dotcpp/main/system/collections/generic/Stack.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    class StackTest
    {
    public:

        static void iteration()
        {
            Stack<String> stringStack;
            stringStack.push("111");
            stringStack.push("222");
            BOOST_CHECK(stringStack.count() == 2);

            for each (cl::String str in stringStack)
            {
                std::cout << str << " ";
            }

            std::cout << std::endl;
        }

        static boost::unit_test::test_suite* StackTestSuite()
        {
            boost::unit_test::test_suite* suite = BOOST_TEST_SUITE("StackTest");
            suite->add(BOOST_TEST_CASE(&StackTest::iteration));
            return suite;
        }


    };
}
