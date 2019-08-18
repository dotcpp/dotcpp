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
#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <iostream>
#include <dot/system/string.hpp>
#include <dot/system/exception.hpp>
#include <dot/system/reflection/method_info.hpp>
#include <dot/system/reflection/constructor_info.hpp>
#include <dot/system/reflection/activator.hpp>
#include <dot/system/type.hpp>
#include <dot/system/collections/generic/list.hpp>


namespace dot
{
    static std::stringstream received;

    class sample_data_impl; using sample_data = ptr<sample_data_impl>;
    class sample_data_2_impl; using sample_data_2 = ptr<sample_data_2_impl>;

    class sample_data_2_impl : public virtual object_impl
    {
        typedef sample_data_2_impl self;

    public: // PROPERTIES

        sample_data data_field;

    public: // STATIC

        static type typeof()
        {
            static type result = []()-> type
            {
                type t = make_type_builder<self>("System.Test", "sample_data_2")
                    ->with_field("data_field", &self::data_field)
                    ->build();

                return t;
            }();

            return result;
        }

        type get_type() override
        {
            return typeof();
        }
    };

    class sample_data_impl; using sample_data = ptr<sample_data_impl>;
    sample_data make_sample_data();

    class sample_data_impl : public virtual object_impl
    {
        typedef sample_data_impl self;  // This typedef will be used inside property macro and inside registration macro.

    public:

        string string_field;
        int int_field;
        double double_field;
        sample_data_2 data_field;
        list<double> double_list_field;

        double foo(int dbl_arg, int int_arg)
        {
            received << "foo(" << dbl_arg << "," << int_arg << ")" << std::endl;
            return dbl_arg + int_arg;
        }

        void bar(int int_arg)
        {
            received << "bar(" << int_arg << ")" << std::endl;
        }

        static void static_foo(int int_arg)
        {
            received << "static_foo(" << int_arg << ")" << std::endl;
        }

    public: // REFLECTION

        DOT_TYPE_BEGIN("System.Test", "sample_data")
            DOT_TYPE_CTOR(make_sample_data)
            ->with_field("string_field", &self::string_field)
            ->with_field("int_field", &self::int_field)
            ->with_field("double_field", &self::double_field)
            ->with_field("data_field", &self::data_field)
            ->with_field("double_list_field", &self::double_list_field)
            DOT_TYPE_METHOD(foo, "dbl_arg", "int_arg")
            DOT_TYPE_METHOD(bar, "int_arg")
            DOT_TYPE_METHOD(static_foo, "int_arg")
        DOT_TYPE_END()
    };

    sample_data make_sample_data() { return new sample_data_impl; }

    string obj_to_string(object obj)
    {
        if (obj.is_empty()) return "";

        type t = obj->get_type();

        std::stringstream ss;

        if (t->name == "List`1")
        {
            list<double> vec = (list<double>)obj;
            for (object item : vec)
            {
                ss << *(obj_to_string(item));
            }

        }
        else if (t == typeof<string>())
        {
            ss << *(string)obj << "|";
        }
        else if (t->is_class)
        {
        }
        else
        {
            ss << *(obj->to_string()) << "|";
        }

        return ss.str();
    }

    TEST_CASE("simple_serialization")
    {
        sample_data obj = make_sample_data();
        obj->string_field = "str";
        obj->data_field = new sample_data_2_impl();
        obj->data_field->data_field = make_sample_data();
        obj->data_field->data_field->string_field = "internal str";
        obj->double_list_field = make_list<double>();
        obj->double_list_field->add(1.);
        obj->double_list_field->add(3.);
        obj->double_list_field->add(2.);

        string s = obj_to_string(obj);

        type t = obj->get_type();

        sample_data dt = (sample_data)activator::create_instance(obj->get_type());

        list<dot::object> paramsFoo = make_list<object>(2);
        paramsFoo[0] = 15;
        paramsFoo[1] = 42;
        double ret = obj->get_type()->get_methods()[0]->invoke(obj, paramsFoo);

        list<dot::object> paramsBar = make_list<object>(1);
        paramsBar[0] = 15;
        obj->get_type()->get_methods()[1]->invoke(obj, paramsBar);

        object o2 = obj->get_type()->get_constructors()[0]->invoke({});
    }
}
