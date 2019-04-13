/*
Copyright (C) 2003-present CompatibL

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

#include <cl/dotcpp/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <iostream>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/reflection/ConstructorInfo.hpp>
#include <cl/dotcpp/main/system/reflection/Activator.hpp>
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>


namespace cl
{
    static std::stringstream received;

    class SampleDataImpl; using SampleData = Ptr<SampleDataImpl>;
    class SampleData2Impl; using SampleData2 = Ptr<SampleData2Impl>;

    class SampleData2Impl : public virtual ObjectImpl
    {
        typedef SampleData2Impl self;

    public: // PROPERTIES

        DOT_AUTO_PROP(SampleData, DataProp)

    public: // STATIC

        static Type typeof()
        {
            static Type type = []()-> Type
            {
                Type type = new_TypeData<self>("System.Test", "SampleData2")
                    ->WithProperty("DataProp", &self::DataProp)

                    ->Build();

                return type;
            }();

            return type;
        }

        virtual Type GetType()
        {
            return typeof();
        }
    };

    class SampleDataImpl; using SampleData = Ptr<SampleDataImpl>;
    SampleData new_SampleData();

    class SampleDataImpl : public virtual ObjectImpl
    {
        typedef SampleDataImpl self;  // This typedef will be used inside property macro and inside registration macro.

    public:

        DOT_AUTO_PROP(String, StringProp)
        DOT_AUTO_PROP(int, IntegerProp)
        DOT_AUTO_PROP(double, DoubleProp)
        DOT_AUTO_PROP(SampleData2, DataProp)
        DOT_AUTO_PROP(List<double>, DblList)

        double Foo(int dblArg, int second_arg)
        {
            received << "Foo(" << dblArg << ")" << std::endl;
            return dblArg + 42;
        }

        void Bar(int intArg)
        {
            received << "Bar(" << intArg << ")" << std::endl;
        }

        static void StaticFoo(int intArg)
        {
            received << "StaticFoo(" << intArg << ")" << std::endl;
        }

    public:

        DOT_REFLECTION
        (
            "System.Test", "SampleData",
            WITH_CONSTRUCTOR(new_SampleData)
            WITH_PROPERTY(StringProp)
            WITH_PROPERTY(DataProp)
            WITH_PROPERTY(DblList)
            WITH_METHOD(Foo, "dbl_arg", "second_arg")
            WITH_METHOD(Bar, "dbl_arg")
            WITH_METHOD(StaticFoo, "g")
        )
    };

    SampleData new_SampleData() { return new SampleDataImpl; }

    String ObjToString(Object obj)
    {
        if (obj.IsEmpty()) return "";

        Type type = obj->GetType();

        std::stringstream ss;

        if (!type->GetInterface("IObjectEnumerable").IsEmpty())
        {
            IObjectEnumerable vec = (IObjectEnumerable)obj;
            for (Object item : vec)
            {
                ss << *(ObjToString(item));
            }

        }
        else if (type == typeof<String>())
        {
            ss << *(String)obj << "|";
        }
        else if (type->IsClass)
        {
            for (PropertyInfo prop : type->GetProperties())
            {
                ss << *(ObjToString(prop->GetValue(obj)));
            }
        }
        else
        {
            ss << *(obj->ToString()) << "|";
        }


        return ss.str();
    }


    TEST_CASE("SimpleSerialization")
    {
        SampleData obj = new_SampleData();
        obj->StringProp = "str";
        obj->DataProp = new SampleData2Impl();
        obj->DataProp->DataProp = new_SampleData();
        obj->DataProp->DataProp->StringProp = "internal str";
        obj->DblList = new_List<double>();
        obj->DblList->Add(1.);
        obj->DblList->Add(3.);
        obj->DblList->Add(2.);

        String s = ObjToString(obj);

        Type type = obj->GetType();

        SampleData dt = (SampleData)Activator::CreateInstance(obj->GetType());

        // obj->StringProp = "abc";
        // obj->IntegerProp = 42;
        // obj->DoubleProp = 1.23;

        //Type type2 = obj2->GetType();
        auto vec_prop = obj->GetType()->GetProperties();

        Array1D<cl::Object> paramsFoo = new_Array1D<Object>(2);
        paramsFoo[0] = 15;
        paramsFoo[1] = 42;
        double ret = obj->GetType()->GetMethods()[0]->Invoke(obj, paramsFoo);

        Array1D<cl::Object> paramsBar = new_Array1D<Object>(1);
        paramsBar[0] = 15;
        obj->GetType()->GetMethods()[1]->Invoke(obj, paramsBar);

        Object o2 = obj->GetType()->GetConstructors()[0]->Invoke({});

        /* TODO - Restore test
        for (PropertyInfo& prop : vec_prop)
        {
            Object val = prop->GetValue(obj);
            String name = prop->Name;
            Type prop_type = prop->PropertyType;
            String prop_type_name = prop_type->Name;
        }

        Approvals::verify(received.str());
        received.clear();
        */
    }
}
