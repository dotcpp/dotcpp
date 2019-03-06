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
#include <cl/dotcpp/test/system/PropertyTest.hpp>

namespace cl
{
    class PropertySample
    {
        std::string value_;

    private: // METHODS

        /// <summary>Method used for property get.</summary>
        static std::string getValue(PropertySample& obj) { return obj.value_; }

        /// <summary>Method used for property set.</summary>
        static void setValue(PropertySample& obj, const std::string& value) { obj.value_ = value; }

    public: // METHOD

        /// <summary>Test property.</summary>
        Property<PropertySample, std::string> Value = Property<PropertySample, std::string>(*this, getValue, setValue);
    };

    /// <summary>Smoke test.</summary>
    void PropertyTest::SmokeTest()
    {
        PropertySample sample;
        sample.Value = "abc";
        std::string v1 = sample.Value;
        sample.Value = "def";
        std::string v2 = sample.Value;
    }

    /// <summary>Includes all test methods in this class.</summary>
    test_suite* PropertyTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("PropertyTest");
        suite->add(BOOST_TEST_CASE(&PropertyTest::SmokeTest));
        return suite;
    }
}
