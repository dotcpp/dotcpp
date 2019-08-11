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
#include <dot/system/object.hpp>
#include <dot/system/enum_impl.hpp>
#include <dot/system/text/string_builder.hpp>
#include <dot/system/collections/generic/dictionary.hpp>

namespace dot
{
    /// Enum sample.
    enum class apples_sample
    {
        /// Empty value.
        empty,

        /// First value.
        red,

        /// Second value.
        gala
    };

    /// Enum sample.
    enum class colors_sample
    {
        /// Empty value.
        empty,

        /// First value.
        blue,

        /// Second value.
        red
    };

    template <>
    struct typeof_impl<apples_sample>
    {
        static type_t get_typeof()
        {
            static type_t result = make_type_builder<char>("dot", "apples_sample")->is_enum()->build();
            return result;
        }
    };

    /// Helper class to implement to_string(value) via template specialization
    template <>
    struct to_string_impl<apples_sample>
    {
        static dot::dictionary<dot::string, int> get_enum_map(int size)
        {
            static dot::dictionary<dot::string, int> func = [size]()
            {
                auto result = dot::make_dictionary<dot::string, int>();
                for (int i = 0; i < size; i++)
                {
                    apples_sample enum_value = (apples_sample)i;
                    string string_value = to_string(enum_value);
                    result[string_value] = i;
                }
                return result;
            }();
            return func;
        }

        /// Convert value to string; for empty or null values, return string::empty.
        static string to_string(const apples_sample& value)
        {
            switch (value)
            {
            case apples_sample::empty: return "empty";
            case apples_sample::red: return "red";
            case apples_sample::gala: return "gala";
            default: throw exception("Unknown enum value in to_string(...).");
            }
        }

        /// Convert value to string; for empty or null values, return string::empty.
        static bool try_parse(string value, apples_sample& result)
        {
            dot::dictionary<dot::string, int> dict = get_enum_map(3); // TODO - size hardcoded, improve
            int int_result;
            if (dict->try_get_value(value, int_result))
            {
                result = (apples_sample)int_result;
                return true;
            }
            else
            {
                result = (apples_sample)0;
                return false;
            }
        }
    };

    TEST_CASE("smoke")
    {
        string_builder received = make_string_builder();

        // Serialization
        received->append_line("Serialization");
        //received->indent++;

        // Serialize
        if (true)
        {
            apples_sample value = apples_sample::red;
            string serialized_value = to_string(value);
            received->append_line(dot::string::format("Serialized={0}", serialized_value));
        }

        // Serialize nullable enum
        if (true)
        {
            // Establish that null.ToString() is String.Empty, not null
            nullable<apples_sample> nullable_value = nullptr;
            string serialized_value = to_string(nullable_value);
            received->append_line(string::format("NullableSerialized(null).IsNull={0}", serialized_value == nullptr));
            received->append_line(string::format("NullableSerialized(null).IsEmpty={0}", serialized_value == string::empty));
        }
        if (true)
        {
            nullable<apples_sample> nullable_value = apples_sample::red;
            string serializedValue = to_string(nullable_value);
            received->append_line(string::format("NullableSerialized(red)={0}", serializedValue));
        }

        // Deserialization
        if (true)
        {
            dot::string str = "red";
            apples_sample result;
            bool success = to_string_impl<apples_sample>::try_parse(str, result);
            received->append_line(dot::string::format("String={0} TryParse={1} Value={2}", str, success, to_string(result)));
        }

        if (true)
        {
            dot::string str = "blue";
            apples_sample result;
            bool success = to_string_impl<apples_sample>::try_parse(str, result);
            received->append_line(dot::string::format("String={0} TryParse={1} Value={2}", str, success, to_string(result)));
        }

        // Boxing
        received->append_line("Boxing");
        //received->indent++;
        
        // Check type of boxed enum
        dot::object boxed = apples_sample::red;
        // received->append_line(dot::string::format("Type(Boxed)={0}", boxed->type()));

        // Unbox to the correct type
        apples_sample unboxed = (enum_impl<apples_sample>)boxed;
        received->append_line(dot::string::format("Boxed={0} Unboxed={1}", boxed->to_string(), to_string(unboxed)));

        // Establish that unboxing DOES enforce enum type, unlike in C#.
        //
        // For added safety, this behavior has been intentionally made different
        // from C# where unboxing DOES NOT enforce enum type. Similar code in
        // C# would have converted the enum based on its integer value.
        CHECK_THROWS((enum_impl<colors_sample>)boxed);

        Approvals::verify(*received);
    }
}
