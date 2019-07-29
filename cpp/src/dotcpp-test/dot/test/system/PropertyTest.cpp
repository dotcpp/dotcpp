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
#include <dot/system/string.hpp>
#include <dot/system/text/stringbuilder.hpp>

namespace dot
{
    static std::stringstream received;

    class PropertySampleBaseDataImpl; using PropertySampleBaseData = ptr<PropertySampleBaseDataImpl>;

    class PropertySampleBaseDataImpl : public virtual object_impl
    {
        friend PropertySampleBaseData new_PropertySampleBaseData();

        typedef PropertySampleBaseDataImpl self;

    private: // FIELDS

        int x_ = 1;

    public: // PROPERTIES

        DOT_GET(int, RegularGet, { return 10; })
        DOT_PROP(int, RegularProp, { return x_; }, { x_ = value; })

        DOT_DECL_GET(int, DeclaredGet)
        DOT_DECL_PROP(int, DeclaredProp)

        DOT_DECL_GET(int, DeclaredGet2)
        DOT_DECL_GET(int, DeclaredGet3)
        DOT_DECL_PROP(int, DeclaredProp2)

    protected: // CONSTRUCTORS

        PropertySampleBaseDataImpl() = default;
    };

    class PropertySampleDataImpl; using PropertySampleData = ptr<PropertySampleDataImpl>;

    class PropertySampleDataImpl : public PropertySampleBaseDataImpl
    {
        friend PropertySampleData new_PropertySampleData();

        typedef PropertySampleDataImpl self;

    private: // FIELDS

        int y_ = 456;

    public: // PROPERTIES

        // Implement declared properties by specifying methods
        DOT_IMPL_GET(int, DeclaredGet, { return 456; })
        DOT_IMPL_PROP(int, DeclaredProp, { return y_; }, { y_ = value; })

        // Implement declared properties as auto properties
        DOT_AUTO_GET(int, DeclaredGet2)
        DOT_AUTO_PROP(int, DeclaredGet3)
        DOT_AUTO_PROP(int, DeclaredProp2)

        // Properties that have native type
        DOT_AUTO_PROP(string, string_prop)
        DOT_AUTO_PROP(int, IntegerProp)
        DOT_AUTO_PROP(double, DoubleProp)

        // Property that is a scalar class
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
        string_builder received = make_string_builder();

        PropertySampleData obj = new_PropertySampleData();
        obj->DeclaredProp = 100;
        obj->DeclaredProp2 = 200;
        obj->DeclaredGet3 = 50;
        obj->RegularProp = 25;
        obj->string_prop = "abc";
        obj->IntegerProp = 123;
        obj->DoubleProp = 3.1415;
        obj->DataProp = new_PropertySampleData();
        obj->DataProp->string_prop = "xyz";

        received->AppendLine(string::Format("RegularGet: {0}", obj->RegularGet));
        received->AppendLine(string::Format("RegularProp: {0}", obj->RegularProp));
        received->AppendLine(string::Format("DeclaredGet: {0}", obj->DeclaredGet));
        received->AppendLine(string::Format("DeclaredGet2: {0}", obj->DeclaredGet2));
        received->AppendLine(string::Format("DeclaredGet3: {0}", obj->DeclaredGet3));
        received->AppendLine(string::Format("DeclaredProp: {0}", obj->DeclaredProp));
        received->AppendLine(string::Format("DeclaredProp2: {0}", obj->DeclaredProp2));
        received->AppendLine(string::Format("string_prop: {0}", std::string(obj->string_prop->c_str())));
        received->AppendLine(string::Format("IntegerProp: {0}", obj->IntegerProp));
        received->AppendLine(string::Format("DoubleProp: {0}", obj->DoubleProp));
        received->AppendLine(string::Format("DataProp->string_prop: {0}", std::string(obj->DataProp->string_prop->c_str())));

        Approvals::verify(*received);
    }
}
