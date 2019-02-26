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

#ifndef cl_dotcpp_test_StackTests_hpp
#define cl_dotcpp_test_StackTests_hpp

#include <cl/system/api/collections/generic/TStack.hpp>

namespace cl {
    typedef std::string String;
}

class TStackTests
{
public:

    static void iteration()
    {
        cl::TStack<cl::String> stringStack;
        stringStack.push("111");
        stringStack.push("222");
        BOOST_CHECK(stringStack.count() == 2);

        for each (cl::String str in stringStack)
        {
            std::cout << str << " ";
        }

        std::cout << std::endl;
    }

    static test_suite* TStackTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("TStack test");
        suite->add(BOOST_TEST_CASE(&TStackTests::iteration));
        return suite;
    }


};

#endif // cl_dotcpp_test_StackTests_hpp
