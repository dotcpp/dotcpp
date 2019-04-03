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

    class PropertySampleBaseDataImpl; using PropertySampleBaseData = Ptr<PropertySampleBaseDataImpl>;

    class PropertySampleBaseDataImpl : public virtual ObjectImpl
    {
        typedef PropertySampleBaseDataImpl ThisType;
        friend PropertySampleBaseData new_PropertySampleBaseData();

    private:
        int x_ = 1;

    public:

        DOT_DECL_GET(int, DeclaredGet)
        DOT_DECL_PROP(int, DeclaredProp)

        // TODO - must be able to declare property and implement as autoproperty
        // DOT_DECL_GET(int, DeclaredGet2)
        // DOT_DECL_GET(int, DeclaredGet3)
        // DOT_DECL_PROP(int, DeclaredProp2)

        DOT_GET(int, RegularGet, { return 123; })
        DOT_PROP(int, RegularProp, { return x_; }, { x_ = value; })

    protected:
        PropertySampleBaseDataImpl() = default;
    };

    class PropertySampleDataImpl; using PropertySampleData = Ptr<PropertySampleDataImpl>;

    class PropertySampleDataImpl : public PropertySampleBaseDataImpl
    {
        typedef PropertySampleDataImpl ThisType;
        friend PropertySampleData new_PropertySampleData();

    private:
        int y_ = 456;

    public:

        DOT_IMPL_GET(int, DeclaredGet, { return 456; })
        DOT_IMPL_PROP(int, DeclaredProp, { return y_; }, { y_ = value; })

        // Implement declared properties as auto properties
        // A property can be declared as get and implemented as get/set
        DOT_AUTO_GET(int, DeclaredGet2)
        DOT_AUTO_PROP(int, DeclaredGet3)
        DOT_AUTO_PROP(int, DeclaredProp2)

        DOT_AUTO_PROP(String, StringProp)
        DOT_AUTO_PROP(int, IntegerProp)
        DOT_AUTO_PROP(double, DoubleProp)
        DOT_AUTO_PROP(PropertySampleData, DataProp)

    protected:
        PropertySampleDataImpl()
        {
            // TODO - make it possible to set getter property in ctor
            // DeclaredGet2 = 300;
        }
    };

    PropertySampleData new_PropertySampleData() { return new PropertySampleDataImpl(); }

    TEST_CASE("PropertySemantics")
    {
        StringBuilder received = new_StringBuilder();

        PropertySampleData obj = new_PropertySampleData();
        obj->DeclaredProp = 100;
        obj->DeclaredProp2 = 200;
        obj->StringProp = "abc";
        obj->IntegerProp = 123;
        obj->DoubleProp = 3.1415;
        obj->DataProp = new_PropertySampleData();
        obj->DataProp->StringProp = "xyz";

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
