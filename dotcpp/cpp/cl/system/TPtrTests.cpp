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

#include <cl/system/implement.hpp>
#include <cl/system/TPtrTests.hpp>
#include <cl/system/collections/generic/TDictionary.hpp>
#include <cl/system/TString.hpp>

namespace cl
{
    template <typename Key, typename Value>
    class TTestDictionary : public TDictionary<Key, Value>
        , public TObject
    {
    public:

        virtual TString toString() const
        {
            return TString();
        }

        static TPtr<TTestDictionary<Key, Value>> create() { return TPtr<TTestDictionary<Key, Value>>(new TTestDictionary<Key, Value>()); }
    };

    template <typename Key, typename Value>
    using Dictionary = TPtr<TTestDictionary<Key, Value>>;


    void TPtrTests::testCreate()
    {
        Dictionary<TString, double> dict
            = new Dictionary<TString, double>();

        dict["Va"] = 56.;

        BOOST_CHECK(dict->containsKey("Va"));
        BOOST_CHECK(dict["Va"] == 56.);
    }

    test_suite* TPtrTests::TPtrTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("TString test");
        suite->add(BOOST_TEST_CASE(&TPtrTests::testCreate));
        return suite;
    }
}
