/*
Copyright (C) 2003-present CompatibL

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to faciliate
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
#include <cl/dotcpp/test/system/StaticPropertyTest.hpp>

namespace cl
{
    class StaticPropertySample
    {
        static std::string value_;
        static std::string getValue() { return value_; }
        static void setValue(const std::string& value) { value_ = value; }

    public:
        /// <summary>Test property.</summary>
        static StaticProperty<std::string> Value;
    };

    std::string StaticPropertySample::value_ = "abc";
    StaticProperty<std::string> StaticPropertySample::Value = StaticProperty<std::string>(StaticPropertySample::getValue, StaticPropertySample::setValue);

    void StaticPropertyTest::Test()
    {
    }

    test_suite* StaticPropertyTest::StaticPropertyTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("StaticPropertyTestSuite");
        suite->add(BOOST_TEST_CASE(&StaticPropertyTest::Test));
        return suite;
    }
}
