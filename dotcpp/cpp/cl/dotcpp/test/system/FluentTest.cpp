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
        typedef FluentSampleBaseDataImpl ThisType;
        friend FluentSampleBaseData new_FluentSampleBaseData();

    private:
        int x_ = 1;

    public:

        DOT_DECL_GET(int, DeclaredGet)
        DOT_DECL_FLUENT(int, DeclaredProp)

        // TODO - must be able to declare property and implement as autoproperty
        // DOT_DECL_GET(int, DeclaredGet2)
        // DOT_DECL_GET(int, DeclaredGet3)
        // DOT_DECL_PROP(int, DeclaredProp2)

        DOT_GET(int, RegularGet, { return 123; })
        DOT_PROP(int, RegularProp, { return x_; }, { x_ = value; })

    protected:
        FluentSampleBaseDataImpl() = default;
    };

    class FluentSampleDataImpl; using FluentSampleData = Ptr<FluentSampleDataImpl>;

    class FluentSampleDataImpl : public FluentSampleBaseDataImpl
    {
        typedef FluentSampleDataImpl ThisType;
        friend FluentSampleData new_FluentSampleData();

    private:
        int y_ = 456;

    public:

        DOT_IMPL_GET(int, DeclaredGet, { return 456; })
        DOT_IMPL_PROP(int, DeclaredProp, { return y_; }, { y_ = value; })

        // Implement declared properties as auto properties
        // A property can be declared as get and implemented as get/set
        DOT_AUTO_GET(int, DeclaredGet2)
        DOT_AUTO_FLUENT(int, DeclaredGet3)
        DOT_AUTO_FLUENT(int, DeclaredProp2)

        DOT_AUTO_FLUENT(String, StringProp)
        DOT_AUTO_FLUENT(int, IntegerProp)
        DOT_AUTO_FLUENT(double, DoubleProp)
        DOT_AUTO_FLUENT(FluentSampleData, DataProp)

    protected:
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
            ->DataProp(new_FluentSampleData()->StringProp("xyz"))
            ->DeclaredProp2(200)
            ->DeclaredProp(100)
            .as<FluentSampleData>();

        received->AppendLine(obj->DeclaredGet);
        received->AppendLine(obj->DeclaredProp);

        // TODO - these lines do not compile
        // received->AppendLine(obj->DeclaredGet2);
        // received->AppendLine(obj->DeclaredGet3);

        // This line is declared the same way but compiles
        received->AppendLine(obj->DeclaredProp2);

        received->AppendLine(obj->StringProp->c_str());
        received->AppendLine(obj->IntegerProp);
        received->AppendLine(obj->DoubleProp);
        received->AppendLine(obj->DataProp->StringProp->c_str());

        Approvals::verify(*received);
    }
}
