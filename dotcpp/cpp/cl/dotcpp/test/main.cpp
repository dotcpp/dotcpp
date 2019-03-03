/*
Copyright (C) 2003-present CompatibL. All rights reserved.

This code contains valuable trade secrets and may be copied, stored, used,
or distributed only in compliance with the terms of a written commercial
license from CompatibL and with the inclusion of this copyright notice.
*/

#include <cl/dotcpp/test/implement.hpp>

//#include <cl/dotcpp/test/system/collections/generic/DictionaryTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/HashSetTest.hpp>
#include <cl/dotcpp/test/system/collections/generic/ListTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/QueueTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/SortedDictionaryTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/SortedListTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/SortedSetTest.hpp>
//#include <cl/dotcpp/test/system/collections/generic/StackTest.hpp>

#include <cl/dotcpp/test/system/DoubleTest.hpp>
#include <cl/dotcpp/test/system/ObjectTest.hpp>
#include <cl/dotcpp/test/system/PtrTest.hpp>
#include <cl/dotcpp/test/system/StringTest.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/impl/unit_test_main.ipp>

using namespace boost::unit_test_framework;


struct pause
{
	~pause()
	{
		system("PAUSE");
	}
};

static pause pause_;


test_suite* init_unit_test_suite(int, char*[])
{
	std::string header =
		"Testing Cl.DotCpp";
	std::string rule = std::string(35, '=');

	BOOST_TEST_MESSAGE(rule);
	BOOST_TEST_MESSAGE(header);
	BOOST_TEST_MESSAGE(rule);
	test_suite* test = BOOST_TEST_SUITE("Cl DotCpp test suite");

	test->add(cl::ListTest::ListTestSuite());
	test->add(cl::DoubleTest::DoubleTestSuite());

	return test;
}

