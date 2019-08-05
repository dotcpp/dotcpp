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
#include <dot/system/array1d.hpp>
#include <dot/system/string.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>
#include <dot/system/reflection/Activator.hpp>
#include <dot/system/type.hpp>
#include <dot/system/collections/generic/list.hpp>


namespace dot
{
    static std::stringstream received;

    class SampleDataImpl; using SampleData = ptr<SampleDataImpl>;
    class SampleData2Impl; using SampleData2 = ptr<SampleData2Impl>;

    class SampleData2Impl : public virtual object_impl
    {
        typedef SampleData2Impl self;

    public: // PROPERTIES

        SampleData data_field;

    public: // STATIC

        static type_t typeof()
        {
            static type_t type = []()-> type_t
            {
                type_t type = make_type_builder<self>("System.Test", "SampleData2")
                    ->with_field("data_field", &self::data_field)
                    ->build();

                return type;
            }();

            return type;
        }

        virtual type_t type()
        {
            return typeof();
        }
    };

    class SampleDataImpl; using SampleData = ptr<SampleDataImpl>;
    SampleData new_SampleData();

    class SampleDataImpl : public virtual object_impl
    {
        typedef SampleDataImpl self;  // This typedef will be used inside property macro and inside registration macro.

    public:

        string string_field;
        int IntegerProp;
        double DoubleProp;
        SampleData2 data_field;
        list<double> double_list_field;

        double Foo(int dblArg, int intArg)
        {
            received << "Foo(" << dblArg << "," << intArg << ")" << std::endl;
            return dblArg + intArg;
        }

        void Bar(int intArg)
        {
            received << "Bar(" << intArg << ")" << std::endl;
        }

        static void StaticFoo(int intArg)
        {
            received << "StaticFoo(" << intArg << ")" << std::endl;
        }

    public: // REFLECTION

        DOT_TYPE_BEGIN("System.Test", "SampleData")
            DOT_TYPE_CTOR(new_SampleData)
            ->with_field("StringProp", &self::string_field)
            ->with_field("data_field", &self::data_field)
            ->with_field("double_list_field", &self::double_list_field)
            DOT_TYPE_METHOD(Foo, "dblArg", "intArg")
            DOT_TYPE_METHOD(Bar, "intArg")
            DOT_TYPE_METHOD(StaticFoo, "intArg")
        DOT_TYPE_END()
    };

    SampleData new_SampleData() { return new SampleDataImpl; }

    string Objto_string(object obj)
    {
        if (obj.is_empty()) return "";

        type_t type = obj->type();

        std::stringstream ss;

        if (type->name == "List`1")
        {
            list<double> vec = (list<double>)obj;
            for (object item : vec)
            {
                ss << *(Objto_string(item));
            }

        }
        else if (type == typeof<string>())
        {
            ss << *(string)obj << "|";
        }
        else if (type->is_class)
        {
        }
        else
        {
            ss << *(obj->to_string()) << "|";
        }


        return ss.str();
    }


    TEST_CASE("SimpleSerialization")
    {
        SampleData obj = new_SampleData();
        obj->string_field = "str";
        obj->data_field = new SampleData2Impl();
        obj->data_field->data_field = new_SampleData();
        obj->data_field->data_field->string_field = "internal str";
        obj->double_list_field = make_list<double>();
        obj->double_list_field->add(1.);
        obj->double_list_field->add(3.);
        obj->double_list_field->add(2.);

        string s = Objto_string(obj);

        type_t type = obj->type();

        SampleData dt = (SampleData)activator::create_instance(obj->type());

        array<dot::object> paramsFoo = make_array<object>(2);
        paramsFoo[0] = 15;
        paramsFoo[1] = 42;
        double ret = obj->type()->get_methods()[0]->invoke(obj, paramsFoo);

        array<dot::object> paramsBar = make_array<object>(1);
        paramsBar[0] = 15;
        obj->type()->get_methods()[1]->invoke(obj, paramsBar);

        object o2 = obj->type()->get_constructors()[0]->invoke({});
    }
}
