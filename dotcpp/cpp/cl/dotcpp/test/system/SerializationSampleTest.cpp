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

#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <iostream>

#include <cl/dotcpp/test/implement.hpp>
#include <approvals/ApprovalTests.hpp>
#include <approvals/Catch.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/reflection/ConstructorInfo.hpp>
#include <cl/dotcpp/main/system/reflection/Activator.hpp>
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>


#define DOT_REFLECTION(registration)                                                              \
        static Type typeof()                                                                      \
        {                                                                                         \
            static Type type = []()-> Type                                                        \
            {                                                                                     \
                                                                                                  \
                Type type = new_TypeData<ThisType>                                                \
                            (boost::core::demangled_name(typeid(ThisType)), "DotCpp.System.Test") \
                                                                                                  \
                    registration                                                                  \
                                                                                                  \
                    ->Build();                                                                    \
                                                                                                  \
                return type;                                                                      \
            }();                                                                                  \
                                                                                                  \
            return type;                                                                          \
        }                                                                                         \
                                                                                                  \
        virtual Type GetType()                                                                    \
        {                                                                                         \
            return typeof();                                                                      \
        }



#define PROPERTY(prop_name)        ->WithProperty(#prop_name, &ThisType::prop_name)
#define METHOD(meth_name, ...)     ->WithMethod(#meth_name, &ThisType::meth_name, { __VA_ARGS__ })
#define CONSTRUCTOR(ctor_name, ...)     ->WithConstructor(&ctor_name, { __VA_ARGS__ })


namespace cl
{
    static std::stringstream received;

    class SampleDataImpl; using SampleData = Ptr<SampleDataImpl>;
    class SampleData2Impl; using SampleData2 = Ptr<SampleData2Impl>;

    class SampleData2Impl : public virtual ObjectImpl
    {
        typedef SampleData2Impl ThisType;

    public:
        DOT_AUTO_PROP(SampleData, DataProp)

        static Type typeof()
        {
            static Type type = []()-> Type
            {
                Type type = new_TypeData<ThisType>("SampleData2", "DotCpp.System.Test")
                    ->WithProperty("DataProp", &ThisType::DataProp)

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
        typedef SampleDataImpl ThisType;  // This typedef will be used inside property macro and inside registration macro.

    public:

        DOT_AUTO_PROP(String, StringProp)
        DOT_AUTO_PROP(int, IntegerProp)
        DOT_AUTO_PROP(double, DoubleProp)
        DOT_AUTO_PROP(SampleData2, DataProp)

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
            CONSTRUCTOR(new_SampleData)
            PROPERTY(StringProp)
            PROPERTY(DataProp)
            METHOD(Foo, "dbl_arg", "second_arg")
            METHOD(Bar, "dbl_arg")
            METHOD(StaticFoo, "g")
        )
    };

    SampleData new_SampleData() { return new SampleDataImpl; }

    TEST_CASE("SimpleSerialization")
    {
        SampleData obj = new_SampleData();
        SampleData2 obj2 = new SampleData2Impl();
        Type type = obj->GetType();

        SampleData dt = (SampleData)Activator::CreateInstance(obj->GetType());

        // obj->StringProp = "abc";
        // obj->IntegerProp = 42;
        // obj->DoubleProp = 1.23;

        Type type2 = obj2->GetType();
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
