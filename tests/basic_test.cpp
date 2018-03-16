#define BOOST_TEST_MAIN

#include "DateTimeGrammars.hpp"

#include <QDateTime>
#include <boost/test/unit_test.hpp>

using namespace DateTimeGrammars;

BOOST_AUTO_TEST_SUITE(Basic)

BOOST_AUTO_TEST_CASE(is_even_test)
{
    BOOST_CHECK(isEven(2));
    BOOST_CHECK(!isEven(3));
}

BOOST_AUTO_TEST_CASE(date_only_test)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    QDate parsed;
    std::string date1 = "2018-12-01";

    std::string::const_iterator begin = date1.begin();
    std::string::const_iterator end = date1.end();

    bool didParse = boost::spirit::qi::parse(begin, end, parser, parsed);
    BOOST_CHECK(didParse);
    BOOST_CHECK((begin == end));    
}

BOOST_AUTO_TEST_SUITE_END()