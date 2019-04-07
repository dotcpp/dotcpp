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
#include "cl/dotcpp/main/system/text/StringBuilder.hpp"

namespace cl
{
    static std::stringstream received;

    class FluentSampleBaseDataImpl; using FluentSampleBaseData = Ptr<FluentSampleBaseDataImpl>;

    class FluentSampleBaseDataImpl : public virtual ObjectImpl
    {
        friend FluentSampleBaseData new_FluentSampleBaseData();

        typedef FluentSampleBaseDataImpl self;

    private: // FIELDS

        int x_ = 1;

    public: // PROPERTIES

        DOT_GET(int, RegularGet, { return 10; })
        DOT_FLUENT(int, RegularProp, { return x_; }, { x_ = value; })

        DOT_DECL_GET(int, DeclaredGet)
        DOT_DECL_FLUENT(int, DeclaredProp)

        DOT_DECL_GET(int, DeclaredGet2)
        DOT_DECL_GET(int, DeclaredGet3)
        DOT_DECL_FLUENT(int, DeclaredProp2)

    protected: // CONSTRUCTORS

        FluentSampleBaseDataImpl() = default;
    };

    class FluentSampleDataImpl; using FluentSampleData = Ptr<FluentSampleDataImpl>;

    class FluentSampleDataImpl : public FluentSampleBaseDataImpl
    {
        friend FluentSampleData new_FluentSampleData();

        typedef FluentSampleDataImpl self;

    private: // FIELDS

        int y_ = 456;

    public: // PROPERTIES

        // Implement declared properties by specifying methods
        DOT_IMPL_GET(int, DeclaredGet, { return 456; })
        DOT_IMPL_FLUENT(int, DeclaredProp, { return y_; }, { y_ = value; })

        // Implement declared properties as auto properties
        DOT_AUTO_GET(int, DeclaredGet2)
        DOT_AUTO_FLUENT(int, DeclaredGet3)
        DOT_AUTO_FLUENT(int, DeclaredProp2)

        // Properties that have native type
        DOT_AUTO_FLUENT(String, StringProp)
        DOT_AUTO_FLUENT(int, IntegerProp)
        DOT_AUTO_FLUENT(double, DoubleProp)

        // Property that is a scalar class
        DOT_AUTO_FLUENT(FluentSampleData, DataProp)

    protected: // CONSTRUCTORS

        FluentSampleDataImpl()
        {
            // TODO - make it possible to set getter property in ctor
            // DeclaredGet2 = 300;
        }
    };

    FluentSampleData new_FluentSampleData() { return new FluentSampleDataImpl(); }

    TEST_CASE("FluentSemantics")
    {
        StringBuilder received = new_StringBuilder();

        FluentSampleData obj = new_FluentSampleData()
            ->StringProp("abc")
            ->IntegerProp(123)
            ->DoubleProp(3.1415)
            ->DataProp(
                new_FluentSampleData()
                ->StringProp("xyz")
                )
            ->DeclaredGet3(50)
            ->DeclaredProp2(200)
            ->DeclaredProp(100)
            ->RegularProp(25)
            .as<FluentSampleData>();

        received->AppendLine(String::Format("RegularGet: {0}", obj->RegularGet));
        received->AppendLine(String::Format("RegularProp: {0}", obj->RegularProp));
        received->AppendLine(String::Format("DeclaredGet: {0}", obj->DeclaredGet));
        received->AppendLine(String::Format("DeclaredGet2: {0}", obj->DeclaredGet2));
        received->AppendLine(String::Format("DeclaredGet3: {0}", obj->DeclaredGet3));
        received->AppendLine(String::Format("DeclaredProp: {0}", obj->DeclaredProp));
        received->AppendLine(String::Format("DeclaredProp2: {0}", obj->DeclaredProp2));
        received->AppendLine(String::Format("StringProp: {0}", std::string(obj->StringProp->c_str())));
        received->AppendLine(String::Format("IntegerProp: {0}", obj->IntegerProp));
        received->AppendLine(String::Format("DoubleProp: {0}", obj->DoubleProp));
        received->AppendLine(String::Format("DataProp->StringProp: {0}", std::string(obj->DataProp->StringProp->c_str())));

        Approvals::verify(*received);
    }
}
