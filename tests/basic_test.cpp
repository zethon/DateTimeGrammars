#define BOOST_TEST_MAIN

#include "DateTimeGrammars.hpp"

#include <QDateTime>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/fusion/adapted/std_tuple.hpp> 

namespace data = boost::unit_test::data;

using namespace DateTimeGrammars;

std::ostream & operator<<(std::ostream & out, const std::tuple<int, int, int> arg)
{
    out 
        << '{' 
        << std::get<0>(arg) 
        << ',' 
        << std::get<1>(arg) 
        << ',' 
        << std::get<2>(arg) 
        << '}';
        
    return out;
}

BOOST_AUTO_TEST_SUITE(Basic)

std::tuple<std::string, unsigned int, unsigned int, unsigned int> dateOnlyGoodData[] = 
{
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "2018-12-11", 2018, 12, 11
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "1969-07-20", 1969, 7, 20
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "2018/12/11", 2018, 12, 11
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "1969/07/20", 1969, 7, 20
    },
};

BOOST_DATA_TEST_CASE(dateOnlyTest, data::make(dateOnlyGoodData), datestring, year, month, day)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    std::string::const_iterator begin = datestring.begin();
    std::string::const_iterator end = datestring.end();

    QDate qdate;
    bool didParse = boost::spirit::qi::parse(begin, end, parser, qdate);

    BOOST_REQUIRE(didParse);
    BOOST_REQUIRE((begin == end));
    BOOST_REQUIRE(qdate.isValid());
    BOOST_REQUIRE(qdate.year() == year);
    BOOST_REQUIRE(qdate.month() == month);
    BOOST_REQUIRE(qdate.day() == day);
}

std::string badDates[] = 
{
    "2018-19-19",
    "2018-99-99",
    "2018-12-0",
    "2018-0-0"
};

BOOST_DATA_TEST_CASE(testBadDates, data::make(badDates), datestring)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    std::string::const_iterator begin = datestring.begin();
    std::string::const_iterator end = datestring.end();

    bool didParse = boost::spirit::qi::parse(begin, end, parser);
    BOOST_REQUIRE(!didParse);
}

BOOST_AUTO_TEST_SUITE_END()