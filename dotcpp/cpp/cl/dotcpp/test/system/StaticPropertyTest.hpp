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

#pragma once

#include <cl/dotcpp/test/declare.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;

#include <cl/dotcpp/main/system/StaticProperty.hpp>

namespace cl
{
    /// <summary>Static property test.</summary>
    class CL_DOTCPP_TEST StaticPropertyTest
    {
    public: // METHODS

        /// <summary>Run test.</summary>
        static void Test();

        static test_suite* StaticPropertyTestSuite();
    };
}
