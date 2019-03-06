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
#include <cl/dotcpp/test/system/ReadOnlyStaticPropertyTest.hpp>

namespace cl
{
    class ReadOnlyStaticPropertySample
    {
        static std::string value_;
        static std::string getValue() { return value_; }

    public:
        /// <summary>Test property</summary>
        static ReadOnlyStaticProperty<std::string> Value;
    };

    std::string ReadOnlyStaticPropertySample::value_ = "abc";
    ReadOnlyStaticProperty<std::string> ReadOnlyStaticPropertySample::Value = ReadOnlyStaticProperty<std::string>(ReadOnlyStaticPropertySample::getValue);

    void ReadOnlyStaticPropertyTest::Test()
    {
    }

    test_suite* ReadOnlyStaticPropertyTest::ReadOnlyStaticPropertyTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("ReadOnlyStaticPropertyTestSuite");
        suite->add(BOOST_TEST_CASE(&ReadOnlyStaticPropertyTest::Test));
        return suite;
    }
}
