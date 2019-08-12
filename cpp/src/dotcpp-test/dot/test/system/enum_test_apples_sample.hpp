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

#include <dot/test/declare.hpp>
#include <dot/system/object.hpp>
#include <dot/system/enum_impl.hpp>
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

    template <>
    struct type_traits<apples_sample>
    {
        static type typeof()
        {
            static type result = make_type_builder<char>("dot", "apples_sample")->is_enum()->build();
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
}
