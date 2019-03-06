/*
Copyright (C) 2003-present CompatibL. All rights reserved.

This code contains valuable trade secrets and may be copied, stored, used,
or distributed only in compliance with the terms of a written commercial
license from CompatibL and with the inclusion of this copyright notice.
*/

#include <cl/dotcpp/test/implement.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/impl/unit_test_main.ipp>
#include <cl/dotcpp/test/system/DoubleTest.hpp>
#include <cl/dotcpp/test/system/ObjectTest.hpp>
#include <cl/dotcpp/test/system/PtrTest.hpp>
#include <cl/dotcpp/test/system/StringTest.hpp>
#include <cl/dotcpp/test/system/collections/generic/ListTest.hpp>
#include <cl/dotcpp/test/system/PropertyTest.hpp>
#include <cl/dotcpp/test/system/ReadOnlyPropertyTest.hpp>
#include <cl/dotcpp/test/system/StaticPropertyTest.hpp>
#include <cl/dotcpp/test/system/ReadOnlyStaticPropertyTest.hpp>

// using namespace boost::unit_test_framework;

#if defined _MSC_VER
struct pause
{
    ~pause()
    {
        system("PAUSE");
    }
};

static pause pause_;
#endif

test_suite* init_unit_test_suite(int, char*[])
{
    std::string header = "Cl.DotCpp.Test";
    std::string rule = std::string(35, '=');

    BOOST_TEST_MESSAGE(rule);
    BOOST_TEST_MESSAGE(header);
    BOOST_TEST_MESSAGE(rule);
    test_suite* allTests = BOOST_TEST_SUITE(header);

    allTests->add(cl::ListTest::ListTestSuite());
    allTests->add(cl::DoubleTest::DoubleTestSuite());
    allTests->add(cl::PropertyTest::GetTestSuite());
    allTests->add(cl::ReadOnlyPropertyTest::GetTestSuite());
    allTests->add(cl::StaticPropertyTest::GetTestSuite());
    allTests->add(cl::ReadOnlyStaticPropertyTest::GetTestSuite());


    return allTests;
}

