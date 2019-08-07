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
#include <dot/system/string.hpp>
#include <dot/system/collections/generic/dictionary.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    dictionary<string, string> Createdictionary()
    {
        dictionary<string, string> dict = make_dictionary<string, string>();

        dict->add("a", "b");
        dict->add(std::pair<string, string>("c", "d"));
        dict->add("", "");

        return dict;
    }

    TEST_CASE("Properties")
    {
        dictionary<string, string> dict = Createdictionary();

        REQUIRE(dict->count() == 3);

        // Keys
        list<string> keys = dict->keys();
        REQUIRE(keys->count() == 3);
        //REQUIRE(keys->contains("a"));  // TODO uncomment when implemented
        //REQUIRE(keys->contains("c"));
        //REQUIRE(keys->contains(""));

        // Values
        list<string> values = dict->values();
        REQUIRE(values->count() == 3);
        //REQUIRE(values->contains("b"));  // TODO uncomment when implemented
        //REQUIRE(values->contains("d"));
        //REQUIRE(values->contains(""));
    }

    TEST_CASE("Methods")
    {
        dictionary<string, string> dict = Createdictionary();

        // Get
        REQUIRE(dict["a"] == "b");
        REQUIRE(dict["c"] == "d");
        REQUIRE(dict[""] == "");

        string s = "";
        dict->try_get_value("b", s);
        REQUIRE(s == "");
        dict->try_get_value("a", s);
        REQUIRE(s == "b");

        REQUIRE(dict->contains_key("a"));
        REQUIRE(dict->contains_key("c"));
        REQUIRE(dict->contains_key(""));
        REQUIRE(dict->contains_key("b") == false);

        REQUIRE(dict->contains_value("b"));
        REQUIRE(dict->contains_value("d"));
        REQUIRE(dict->contains_value(""));
        REQUIRE(dict->contains_value("a") == false);

        // Remove
        dict->remove("a");
        REQUIRE(dict->count() == 2);
        REQUIRE(dict->contains_key("a") == false);
        REQUIRE(dict->contains_value("b") == false);

        // Clear
        dict->clear();
        REQUIRE(dict->count() == 0);
    }

    TEST_CASE("Interfaces")
    {
        dictionary<string, string> dict = make_dictionary<string, string>();
        dict->add("a", "b");
        dict->add("c", "d");
        dict->add("e", "f");

        REQUIRE(dict["a"] == "b");
        REQUIRE(dict["c"] == "d");
        REQUIRE(dict["e"] == "f");
    }

    TEST_CASE("object key")
    {
        object obj0 = make_object();
        object obj1 = make_object();
        object obj2 = object("str2");
        object obj3 = object("str2");

        dictionary<object, string> dict = make_dictionary<object, string>();
        dict->add(obj0, "val0");
        CHECK_NOTHROW(dict->add(obj1, "val1"));

        dict->add(obj2, "val2");
        CHECK_THROWS(dict->add(obj3, "val3"));

        REQUIRE(dict[obj0] == "val0");
        REQUIRE(dict[obj1] == "val1");
        REQUIRE(dict[obj2] == "val2");
        REQUIRE(dict[obj3] == "val2");
    }
}
