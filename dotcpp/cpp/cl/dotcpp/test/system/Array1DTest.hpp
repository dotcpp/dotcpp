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

namespace cl
{
    /// <summary>List test.</summary>
    class CL_DOTCPP_TEST Array1DTest
    {
    public: // METHODS

        /// <summary>Smoke test.</summary>
        static void Smoke();

        /// <summary>Test interfaces.</summary>
        static void Interfaces();

        /// <summary>Test iterators.</summary>
        static void Iterators();

        /// <summary>Test capacity.</summary>
        static void Capacity();

        /// <summary>Test find methods.</summary>
        static void Find();

        /// <summary>Test enumerator methods.</summary>
        static void Enumerator();

        static test_suite* GetTestSuite();

    private:
        /// <summary>Sort vector in ascending order.</summary>
        static void SortDoubleVector(std::vector<double>& v)
        {
            // Sort the argument std::vector<double>
            std::sort(v.begin(), v.end());
        }
    };
}
