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
#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    class BaseImpl : public virtual ObjectImpl
    {
    public:

        virtual std::string foo()
        {
            return "Base";
        }
    };

    using Base = Ptr<BaseImpl>;
    Base new_Base() { return new BaseImpl; }

    class DerivedImpl : public BaseImpl
    {
    public:

        virtual std::string foo()
        {
            return "Derived";
        }

    };

    using Derived = Ptr<DerivedImpl>;
    Derived new_Derived() { return new DerivedImpl; }

    TEST_CASE("Smoke")
    {
        Base b = new_Base();
        REQUIRE(b->foo() == "Base");

        // Check assignment operator
        b = new_Derived();
        REQUIRE(b->foo() == "Derived");

        // Check ctor from derived
        Base d = new_Derived();
        REQUIRE(d->foo() == "Derived");
    }

    TEST_CASE("Cast")
    {
        Base b = new_Base();

        REQUIRE(b.is<Base>() == true);
        REQUIRE(b.is<Derived>() == false);

        REQUIRE(b.as<Base>() != nullptr);
        REQUIRE(b.as<Derived>() == nullptr);


        REQUIRE((Base)b != nullptr);
        CHECK_THROWS_AS(Derived(b), std::runtime_error);

        Base bd = new_Derived();

        REQUIRE(bd.is<Base>() == false);
        REQUIRE(bd.is<Derived>() == true);

        REQUIRE(bd.as<Base>() != nullptr);
        REQUIRE(bd.as<Derived>() != nullptr);

        REQUIRE((Base)bd != nullptr);
        REQUIRE((Derived)bd != nullptr);

        Derived d = new_Derived();

        REQUIRE(d.is<Base>() == false);
        REQUIRE(d.is<Derived>() == true);

        REQUIRE(d.as<Base>() != nullptr);
        REQUIRE(d.as<Derived>() != nullptr);

        REQUIRE((Base)d != nullptr);
        REQUIRE((Derived)d != nullptr);
    }
}
