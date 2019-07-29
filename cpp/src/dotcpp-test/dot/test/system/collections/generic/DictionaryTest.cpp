/*
Copyright (C) 2015-present The DotCpp Authors.

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

#include <dot/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <dot/system/String.hpp>
#include <dot/system/collections/generic/Dictionary.hpp>
#include <dot/system/Type.hpp>

namespace dot
{
    Dictionary<String, String> CreateDictionary()
    {
        Dictionary<String, String> dict = new_Dictionary<String, String>();

        dict->Add("a", "b");
        dict->Add(KeyValuePair<String, String>("c", "d"));
        dict->Add("", "");

        return dict;
    }

    TEST_CASE("Properties")
    {
        Dictionary<String, String> dict = CreateDictionary();

        REQUIRE(dict->Count == 3);

        // Keys
        ICollection<String> keys = dict->Keys;
        REQUIRE(keys->Count == 3);
        //REQUIRE(keys->Contains("a"));  // TODO uncomment when implemented
        //REQUIRE(keys->Contains("c"));
        //REQUIRE(keys->Contains(""));

        // Values
        ICollection<String> values = dict->Values;
        REQUIRE(values->Count == 3);
        //REQUIRE(values->Contains("b"));  // TODO uncomment when implemented
        //REQUIRE(values->Contains("d"));
        //REQUIRE(values->Contains(""));
    }

    TEST_CASE("Methods")
    {
        Dictionary<String, String> dict = CreateDictionary();

        // Get
        REQUIRE(dict["a"] == "b");
        REQUIRE(dict["c"] == "d");
        REQUIRE(dict[""] == "");

        String s = "";
        dict->TryGetValue("b", s);
        REQUIRE(s == "");
        dict->TryGetValue("a", s);
        REQUIRE(s == "b");

        // Contains
        REQUIRE(dict->Contains(KeyValuePair<String, String>("a", "b")));
        REQUIRE(dict->Contains(KeyValuePair<String, String>("c", "d")));
        REQUIRE(dict->Contains(KeyValuePair<String, String>("", "")));

        REQUIRE(dict->ContainsKey("a"));
        REQUIRE(dict->ContainsKey("c"));
        REQUIRE(dict->ContainsKey(""));
        REQUIRE(dict->ContainsKey("b") == false);

        REQUIRE(dict->ContainsValue("b"));
        REQUIRE(dict->ContainsValue("d"));
        REQUIRE(dict->ContainsValue(""));
        REQUIRE(dict->ContainsValue("a") == false);

        // Remove
        dict->Remove("a");
        REQUIRE(dict->Count == 2);
        REQUIRE(dict->ContainsKey("a") == false);
        REQUIRE(dict->ContainsValue("b") == false);

        // Clear
        dict->Clear();
        REQUIRE(dict->Count == 0);
    }

    TEST_CASE("Interfaces")
    {
        Dictionary<String, String> dict = new_Dictionary<String, String>();

        IDictionary<String, String> idict = dict;
        idict->Add("a", "b");
        idict->Add("c", "d");
        idict->Add("e", "f");

        REQUIRE(dict["a"] == "b");
        REQUIRE(dict["c"] == "d");
        REQUIRE(dict["e"] == "f");
    }

    TEST_CASE("object key")
    {
        object obj0 = new_object();
        object obj1 = new_object();
        object obj2 = object("str2");
        object obj3 = object("str2");

        Dictionary<object, String> dict = new_Dictionary<object, String>();
        dict->Add(obj0, "val0");
        CHECK_NOTHROW(dict->Add(obj1, "val1"));

        dict->Add(obj2, "val2");
        CHECK_THROWS(dict->Add(obj3, "val3"));

        REQUIRE(dict[obj0] == "val0");
        REQUIRE(dict[obj1] == "val1");
        REQUIRE(dict[obj2] == "val2");
        REQUIRE(dict[obj3] == "val2");
    }
}
