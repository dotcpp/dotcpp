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
#include "dot/system/collections/generic/dictionary.hpp"
#include <dot/system/enum.hpp>

namespace dot
{
    class enum_sample_2 : public enum_base
    {
        typedef enum_sample_2 self;

    public:
        enum enum_type
        {
            empty,
            first,
            second
        };
    private:
        static dot::object make_self() { return self(); }

    public:
        typedef self element_type;
        typedef dot::struct_wrapper_impl<self>* pointer_type;
        using dot::enum_base::enum_base;

        operator dot::object() { return new dot::struct_wrapper_impl<self>(*this); }
        operator int() const { return value_; }
        self& operator=(int rhs) { value_ = rhs; return *this; }
        self& operator=(const self& other) { value_ = other.value_; return *this; }
        virtual dot::type_t type() { return typeof(); }
        static dot::type_t typeof()
        {
            static dot::type_t type = []()->dot::type_t
            {
                dot::type_t type = dot::make_type_builder<self>("dot", "enum_sample_2")
                    ->is_enum()
                    ->with_constructor(&self::make_self, {})
                    ->with_base<enum_base>()
                    ->build();
                return type;
            }();
            return type;
        }

    protected:
        virtual dot::dictionary<dot::string, int> get_enum_map() override
        {
            static dot::dictionary<dot::string, int> enum_map_ = []()
            {
                auto map_ = dot::make_dictionary<dot::string, int>();
                map_["empty"] = empty;
                map_["first"] = first;
                map_["second"] = second;
                return map_;
            }();

            return enum_map_;
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
            enum_sample_2 value = enum_sample_2::first;
            string serialized_value = value.to_string();
            received->append_line(dot::string::format("Serialized={0}", serialized_value));
        }

        // Serialize nullable enum
        if (true)
        {
            // Establish that null.ToString() is String.Empty, not null
            nullable<enum_sample_2> nullable_value = nullptr;
          //  string serialized_value = nullable_value.to_string();
           // received->append_line(string::format("NullableSerialized(null).IsNull={0}", serialized_value == nullptr));
         //   received->append_line(string::format("NullableSerialized(null).IsEmpty={0}", serialized_value == string::empty));
        }
        if (true)
        {
            nullable<enum_sample_2> nullable_value = enum_sample_2::first;
      //      string serializedValue = to_string(nullable_value);
       //     received->append_line(string::format("NullableSerialized(First)={0}", serializedValue));
        }

        // Deserialization
        if (true)
        {
           // enum_sample_2 result = (enum_sample_2)enum_sample_2::parse("first");
           // received->append_line(dot::string::format("TryParse={0} Value={1}", success, to_string(result)));
        }

        Approvals::verify(*received);
    }
}
