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
#include <cl/dotcpp/test/system/PropertyTest.hpp>

namespace cl
{
    class PropertySample
    {
        std::string value_ = "abc";
        static std::string getValue(PropertySample& obj) { return obj.value_; }
        static void setValue(PropertySample& obj, const std::string& value) { obj.value_ = value; }

    public:
        /// <summary>Test property.</summary>
        Property<PropertySample, std::string> Value = Property<PropertySample, std::string>(*this, getValue, setValue);
    };


    void PropertyTest::Test()
    {
        PropertySample sample;
        std::string v1 = sample.Value;
        sample.Value = "def";
        std::string v2 = sample.Value;
    }

    test_suite* PropertyTest::PropertyTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("PropertyTestSuite");
        suite->add(BOOST_TEST_CASE(&PropertyTest::Test));
        return suite;
    }
}
