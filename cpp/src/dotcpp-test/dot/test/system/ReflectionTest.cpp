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
#include <dot/system/Array1D.hpp>
#include <dot/system/String.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/reflection/PropertyInfo.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>
#include <dot/system/Type.hpp>
#include <dot/system/collections/generic/List.hpp>

namespace dot
{
    static std::stringstream received;

    class ReflectionBaseSampleImpl : public virtual ObjectImpl
    {
        typedef ReflectionBaseSampleImpl self;

    public: // FIELDS

        int IntFld;
        double DblFld;
        List<double> DblListFld;

    public: // PROPERTIES

        DOT_PROP(int, Count,
            {
                received << "ReflectionBaseSample.getCount" << std::endl;
                return Count;
            },
            {
                received << "ReflectionBaseSample.setCount" << std::endl;
                Count = value;
            }
        )

        DOT_GET(int, Count2,
            {
                received << "ReflectionBaseSample.getCount2" << std::endl;
                return Count2;
            }
        )

    private: // FIELDS

        int PrivateIntFld = 42;

    public: // METHODS

        int SampleMethod(int param)
        {
            received << "Invoked ReflectionBaseSample.SampleMethod";
            return 42 + param;
        }

        virtual Type GetType()
        {
            // Converts to Type with thread safety guarantee as per C++ Standard
            static Type typeLambda = []()->Type
            {
                received << "Creating Type (this should run only once)." << std::endl;

                return new_TypeBuilder<ReflectionBaseSampleImpl>("System.Test", "ReflectionBaseSample")

                    //->WithProperty("IntFld", &ReflectionBaseSampleImpl::IntFld)
                    //->WithProperty("PrivateIntFld", &ReflectionBaseSampleImpl::PrivateIntFld)
                    //->WithProperty("Count", &ReflectionBaseSampleImpl::Count)
                    //->WithProperty("Count2", &ReflectionBaseSampleImpl::Count2)

                    ->Build();

                /*
                data->Properties = new_Array1D<PropertyInfo>(4);
                data->Properties[0] = new_PropertyInfo("IntFld", type, nullptr, &ReflectionBaseSampleImpl::IntFld);
                data->Properties[1] = new_PropertyInfo("PrivateIntFld", type, nullptr, &ReflectionBaseSampleImpl::PrivateIntFld);
                data->Properties[2] = new_PropertyInfo("Count", type, nullptr, &ReflectionBaseSampleImpl::Count);
                data->Properties[3] = new_PropertyInfo("Count2", type, nullptr, &ReflectionBaseSampleImpl::Count2 );

                data->Methods = new_Array1D<MethodInfo>(1);
                data->Methods[0] = new_MethodInfo("SampleMethod", type, &ReflectionBaseSampleImpl::SampleMethod); // TODO - not part of C# API, use builder pattern for MethodInfo
                data->Methods[0]->Parameters = new_Array1D<ParameterInfo>(1);
                data->Methods[0]->Parameters[0] = new_ParameterInfo("param", nullptr, 0);
                */
            }();

            return typeLambda;
        }
    };

    using ReflectionBaseSample = ptr<ReflectionBaseSampleImpl>;
    ReflectionBaseSample new_ReflectionBaseSample() { return new ReflectionBaseSampleImpl; }

    class ReflectionDerivedSampleImpl : public ReflectionBaseSampleImpl
    {
    public: // PROPERTIES

        DOT_IMPL_PROP(int, Count,
            {
                received << "ReflectionDerivedSample.getCount" << std::endl;
                return Count;
            },
            {
                received << "ReflectionDerivedSample.setCount" << std::endl;
                Count = value;
            }
        )
    };

    using ReflectionDerivedSample = ptr<ReflectionDerivedSampleImpl>;
    ReflectionDerivedSample new_ReflectionDerivedSample() { return new ReflectionDerivedSampleImpl; }

    TEST_CASE("PropertyInfo")
    {
        // TODO - enable
        /*
        ReflectionBaseSample obj = new_ReflectionBaseSample();
        obj->IntFld = 15;
        obj->Count = 15;

        Object x = obj->Count;

        Type type = obj->GetType();
        Array1D<PropertyInfo> props = type->GetProperties();
        PropertyInfo int_prop = props[0];
        REQUIRE(int_prop->Name == "IntFld");
        REQUIRE(int(int_prop->GetValue(obj)) == 15);

        int_prop->SetValue(obj, 19);
        REQUIRE(obj->IntFld == 19);
        REQUIRE(int(int_prop->GetValue(obj)) == 19);

        PropertyInfo private_int_prop = props[1];
        REQUIRE(private_int_prop->Name == "PrivateIntFld");
        REQUIRE(int(private_int_prop->GetValue(obj)) == 42);

        props[2]->SetValue(obj, 2384);
        REQUIRE(obj->Count == 2384);
        REQUIRE(int(props[2]->GetValue(obj)) == 2384);

        ReflectionDerivedSample obj2 = new_ReflectionDerivedSample();

        props[2]->SetValue(obj2, -15);
        REQUIRE(obj2->Count == -15);
        REQUIRE(int(props[2]->GetValue(obj2)) == -15);

        Array1D<Object> params = new_Array1D<Object>(1);
        params[0] = 15;
        REQUIRE(int(type->GetMethods()[0]->Invoke(obj2, params)) == 42 + 15);
        */
        //Approvals::verify(received.str());
        received.clear();
    }
}
