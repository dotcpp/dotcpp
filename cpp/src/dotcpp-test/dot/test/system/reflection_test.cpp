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
#include <dot/system/Exception.hpp>
#include <dot/system/reflection/method_info.hpp>
#include <dot/system/reflection/constructor_info.hpp>
#include <dot/system/type.hpp>
#include <dot/system/collections/generic/list.hpp>

namespace dot
{
    static std::stringstream received;

    class reflection_base_sample_impl : public virtual object_impl
    {
        typedef reflection_base_sample_impl self;

    public: // FIELDS

        int int_field;
        double double_field;
        list<double> double_list_field_field;

    public: // METHODS

        int sample_method(int param)
        {
            received << "Invoked reflection_base_sample.sample_method";
            return 42 + param;
        }

        virtual type_t type()
        {
            // Converts to type_t with thread safety guarantee as per C++ Standard
            static type_t type = []()->type_t
            {
                received << "Creating type_t (this should run only once)." << std::endl;

                return make_type_builder<reflection_base_sample_impl>("System.Test", "reflection_base_sample")

                    //->WithProperty("IntFld", &reflection_base_sample_impl::IntFld)
                    //->WithProperty("PrivateIntFld", &reflection_base_sample_impl::PrivateIntFld)
                    //->WithProperty("Count", &reflection_base_sample_impl::Count)
                    //->WithProperty("Count2", &reflection_base_sample_impl::Count2)

                    ->build();
            }();

            return type;
        }
    };

    using reflection_base_sample = ptr<reflection_base_sample_impl>;
    reflection_base_sample make_reflection_base_sample() { return new reflection_base_sample_impl; }

    class reflection_derived_sample_impl : public reflection_base_sample_impl
    {
    public: // FIELDS

        int int_field_in_derived_class;
    };

    using reflection_derived_sample = ptr<reflection_derived_sample_impl>;
    reflection_derived_sample make_reflection_derived_sample() { return new reflection_derived_sample_impl; }

    TEST_CASE("property_info")
    {
        // TODO - enable
        /*
        reflection_base_sample obj = make_reflection_base_sample();
        obj->IntFld = 15;
        obj->count() = 15;

        object x = obj->count();

        type_t type = obj->type();
        list<property_info> props = type->get_properties();
        property_info int_prop = props[0];
        REQUIRE(int_prop->Name == "IntFld");
        REQUIRE(int(int_prop->GetValue(obj)) == 15);

        int_prop->SetValue(obj, 19);
        REQUIRE(obj->IntFld == 19);
        REQUIRE(int(int_prop->GetValue(obj)) == 19);

        property_info private_int_prop = props[1];
        REQUIRE(private_int_prop->Name == "PrivateIntFld");
        REQUIRE(int(private_int_prop->GetValue(obj)) == 42);

        props[2]->SetValue(obj, 2384);
        REQUIRE(obj->count() == 2384);
        REQUIRE(int(props[2]->GetValue(obj)) == 2384);

        reflection_derived_sample obj2 = make_reflection_derived_sample();

        props[2]->SetValue(obj2, -15);
        REQUIRE(obj2->count() == -15);
        REQUIRE(int(props[2]->GetValue(obj2)) == -15);

        list<object> params = make_list<object>(1);
        params[0] = 15;
        REQUIRE(int(type->GetMethods()[0]->Invoke(obj2, params)) == 42 + 15);
        */
        //Approvals::verify(received.str());
        received.clear();
    }
}
