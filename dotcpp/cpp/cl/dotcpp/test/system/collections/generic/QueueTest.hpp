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

#ifndef cl_dotcpp_test_QueueTests_hpp
#define cl_dotcpp_test_QueueTests_hpp

#include <cl/dotcpp/main/system/collections/generic/Queue.hpp>

namespace cl {
    typedef std::string String;
}

class CL_SYSTEM TQueueTests
{
public:

    static void iteration()
    {
        cl::TQueue<cl::String> stringQueue;
        stringQueue.enqueue("111");
        stringQueue.enqueue("222");
        BOOST_CHECK(stringQueue.getCount() == 2);

        for each (cl::String str in stringQueue)
        {
            std::cout << str << " ";
        }
        std::cout << std::endl;
        BOOST_CHECK(stringQueue.peek() == "111");
        stringQueue.dequeue();
        stringQueue.dequeue();
        BOOST_CHECK(stringQueue.getCount() == 0);
    }

    static test_suite* TQueueTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("TQueue test");
        suite->add(BOOST_TEST_CASE(&TQueueTests::iteration));
        return suite;
    }


};

#endif // cl_dotcpp_test_QueueTests_hpp
