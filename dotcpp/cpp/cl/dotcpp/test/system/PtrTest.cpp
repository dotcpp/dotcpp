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
#include <cl/dotcpp/test/system/PtrTest.hpp>

namespace cl
{
    class BaseImpl
    {
    public:

        virtual ~BaseImpl() {}

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
        virtual ~DerivedImpl() {}

        virtual std::string foo()
        {
            return "Derived";
        }

    };

    using Derived = Ptr<DerivedImpl>;
    Derived new_Derived() { return new DerivedImpl; }

    void PtrTest::Inheritance()
    {
        Base b = new_Base();
        BOOST_CHECK(b->foo() == "Base");

        // Check assignment operator
        b = new_Derived();
        BOOST_CHECK(b->foo() == "Derived");

        // Check ctor from derived
        Base d = new_Derived();
        BOOST_CHECK(d->foo() == "Derived");
    }

    void PtrTest::Cast()
    {
        Base b = new_Base();

        BOOST_CHECK(b.is<Base>() == true);
        BOOST_CHECK(b.is<Derived>() == false);

        BOOST_CHECK(b.as<Base>() != nullptr);
        BOOST_CHECK(b.as<Derived>() == nullptr);

        BOOST_CHECK(b.cast<Base>() != nullptr);
        BOOST_CHECK_THROW(b.cast<Derived>(), std::runtime_error);

        Base bd = new_Derived();

        BOOST_CHECK(bd.is<Base>() == false);
        BOOST_CHECK(bd.is<Derived>() == true);

        BOOST_CHECK(bd.as<Base>() != nullptr);
        BOOST_CHECK(bd.as<Derived>() != nullptr);

        BOOST_CHECK(bd.cast<Base>() != nullptr);
        BOOST_CHECK(bd.cast<Derived>() != nullptr);

        Derived d = new_Derived();

        BOOST_CHECK(d.is<Base>() == false);
        BOOST_CHECK(d.is<Derived>() == true);

        BOOST_CHECK(d.as<Base>() != nullptr);
        BOOST_CHECK(d.as<Derived>() != nullptr);

        BOOST_CHECK(d.cast<Base>() != nullptr);
        BOOST_CHECK(d.cast<Derived>() != nullptr);
    }

    test_suite* PtrTest::GetTestSuite()
    {
        test_suite* suite = BOOST_TEST_SUITE("PtrTest");
        suite->add(BOOST_TEST_CASE(&PtrTest::Inheritance));
        suite->add(BOOST_TEST_CASE(&PtrTest::Cast));
        return suite;
    }
}
