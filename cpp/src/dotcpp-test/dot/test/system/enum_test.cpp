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
#include "dot/system/text/string_builder.hpp"

namespace dot
{
    /// Enum sample.
    enum class enum_sample
    {
        /// Empty value.
        empty,

        /// First value.
        first,

        /// Second value.
        second
    };

    /// Get type_t object for the argument.
    type_t typeof(enum_sample value)
    {
        static type_t result = make_type_builder<enum_sample>("dot", "enum_sample")
            ->is_enum()
            ->build();
        return result;
    }

    /// Convert to string, applying enum case conversion settings to the result
    dot::string to_string(enum_sample value)
    {
        switch (value)
        {
        case enum_sample::empty: return "empty";
        case enum_sample::first: return "first";
        case enum_sample::second: return "second";
        default: throw exception("Unknown enum value in to_string(enum_sample).");
        }
    }

    TEST_CASE("smoke")
    {
        string_builder received = make_string_builder();

        // Serialization
        received->append_line("Serialization");
        //received->indent++;

        // Serialize
        enum_sample value = enum_sample::first;
        string serialized_value = to_string(value);
        received->append_line(dot::string::format("Serialized={0}", serialized_value));

        Approvals::verify(*received);
    }
}
