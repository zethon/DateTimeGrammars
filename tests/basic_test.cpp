#include "DateTimeGrammars.hpp"

#include <boost/test/unit_test.hpp>

using namespace DateTimeGrammars;

BOOST_AUTO_TEST_SUITE(Basic)

BOOST_AUTO_TEST_CASE(is_even_test)
{
    BOOST_CHECK(isEven(2));
    BOOST_CHECK(!isEven(3));
}

BOOST_AUTO_TEST_SUITE_END()