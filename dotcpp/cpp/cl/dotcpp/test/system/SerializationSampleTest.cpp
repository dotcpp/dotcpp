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
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>

namespace cl
{
    static std::stringstream received;

    class SampleDataImpl; using SampleData = Ptr<SampleDataImpl>;
    class SampleData2Impl; using SampleData2 = Ptr<SampleData2Impl>;

    class SampleData2Impl : public virtual ObjectImpl
    {
    public:
        DOT_AUTO_PROP(SampleData2Impl, SampleData, DataProp)

        static Type typeof()
        {
            static Type type = []()-> Type
            {
                Type type = new_TypeData<SampleData2Impl>("SampleData2", "DotCpp.System.Test")
                    ->WithProperty("DataProp", &SampleData2Impl::DataProp)

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

    class SampleDataImpl : public virtual ObjectImpl
    {
    public:

        DOT_AUTO_PROP(SampleDataImpl, String, StringProp)
        DOT_AUTO_PROP(SampleDataImpl, int, IntegerProp)
        DOT_AUTO_PROP(SampleDataImpl, double, DoubleProp)
        DOT_AUTO_PROP(SampleDataImpl, SampleData2, DataProp)

        double Foo(int dblArg)
        {
            received << "Foo(" << dblArg << ")" << std::endl;
            return dblArg + 42;
        }

        void Bar(int intArg)
        {
            received << "Bar( << intArg << ")" << std::endl;
        }

        static void StaticFoo(int intArg)
        {
            received << "StaticFoo( << intArg << ")" << std::endl;
        }

    public:
        static Type typeof()
        {
            static Type type = []()-> Type
            {
                Type type = new_TypeData<SampleDataImpl>("SampleData", "DotCpp.System.Test")
                    ->WithProperty("IntegerProp", &SampleDataImpl::StringProp)
                    ->WithProperty("DataProp", &SampleDataImpl::DataProp)
                    ->WithMethod("Foo", &SampleDataImpl::Foo, {"dblArg"})
                    ->WithMethod("Bar", &SampleDataImpl::Bar, { "dblArg" })
                    ->WithMethod("StaticFoo", &SampleDataImpl::StaticFoo, { "intArg" })

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

    using SampleData = Ptr<SampleDataImpl>;
    SampleData new_SampleData() { return new SampleDataImpl; }

    TEST_CASE("SimpleSerialization")
    {
        SampleData obj = new_SampleData();
        SampleData2 obj2 = new SampleData2Impl();
        // obj->StringProp = "abc";
        // obj->IntegerProp = 42;
        // obj->DoubleProp = 1.23;

        Type type2 = obj2->GetType();
        auto vec_prop = obj->GetType()->GetProperties();
        Array1D<cl::Object> param = new_Array1D<Object>(1);
        param[0] = 15;
        double ret = obj->GetType()->GetMethods()[0]->Invoke(obj, param);
        obj->GetType()->GetMethods()[1]->Invoke(obj, param);

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
