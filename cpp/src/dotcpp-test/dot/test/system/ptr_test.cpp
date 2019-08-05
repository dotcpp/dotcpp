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
#include <dot/system/object.hpp>

namespace dot
{
    class base_impl : public virtual object_impl
    {
    public:

        virtual std::string foo()
        {
            return "base";
        }
    };

    using base = ptr<base_impl>;
    base new_base() { return new base_impl; }

    class derived_impl : public base_impl
    {
    public:

        virtual std::string foo()
        {
            return "derived";
        }

    };

    using derived = ptr<derived_impl>;
    derived new_derived() { return new derived_impl; }

    TEST_CASE("Smoke")
    {
        base b = new_base();
        REQUIRE(b->foo() == "base");

        // Check assignment operator
        b = new_derived();
        REQUIRE(b->foo() == "derived");

        // Check ctor from derived
        base d = new_derived();
        REQUIRE(d->foo() == "derived");
    }

    TEST_CASE("Cast")
    {
        base b = new_base();

        REQUIRE(b.is<base>() == true);
        REQUIRE(b.is<derived>() == false);

        REQUIRE(b.as<base>() != nullptr);
        REQUIRE(b.as<derived>() == nullptr);


        REQUIRE((base)b != nullptr);
        CHECK_THROWS_AS(derived(b), std::runtime_error);

        base bd = new_derived();

        REQUIRE(bd.is<base>() == true);
        REQUIRE(bd.is<derived>() == true);

        REQUIRE(bd.as<base>() != nullptr);
        REQUIRE(bd.as<derived>() != nullptr);

        REQUIRE((base)bd != nullptr);
        REQUIRE((derived)bd != nullptr);

        derived d = new_derived();

        REQUIRE(d.is<base>() == true);
        REQUIRE(d.is<derived>() == true);

        REQUIRE(d.as<base>() != nullptr);
        REQUIRE(d.as<derived>() != nullptr);

        REQUIRE((base)d != nullptr);
        REQUIRE((derived)d != nullptr);
    }
}
