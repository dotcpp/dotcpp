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

    class SampleDataImpl : public virtual ObjectImpl
    {
    public:

    DOT_AUTO_PROP(SampleDataImpl, String, StringProp)
    DOT_AUTO_PROP(SampleDataImpl, int, IntegerProp)
    DOT_AUTO_PROP(SampleDataImpl, double, DoubleProp)


        double foo(int dbl_arg)
        {
            return dbl_arg + 42;
        }

    public:
        static Type typeof()
        {
            static Type type = []()-> Type
            {
                Type type = new_TypeData()
                    ->WithName("SampleData")
                    ->WithNamespace("DotCpp.System.Test")
                    ->WithProperty("IntegerProp", &SampleDataImpl::IntegerProp)
                    ->WithMethod("foo", &SampleDataImpl::foo, {"dbl_arg"})

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
    //    obj->StringProp = "abc";
     //   obj->IntegerProp = 42;
      //  obj->DoubleProp = 1.23;

        auto vec_prop = obj->GetType()->GetProperties();
        Array1D<cl::Object> param = new_Array1D<Object>(1);
        param[0] = 15;
        double ret = obj->GetType()->GetMethods()[0]->Invoke(obj, param);

        /*for (PropertyInfo& prop : vec_prop)
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
