#define BOOST_TEST_MAIN

#include "DateTimeGrammars.hpp"

#include <QDateTime>
#include <QDebug>

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
    // YYYY-MM-DD
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

    // DD-MM-YYYY
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "17/03/2004", 2004, 3, 17
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "29/2/1976", 1976, 2, 29
    },

    // MON DD,YYYY
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "feb 16, 2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "feb 16,2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "feb 16 2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "jUN 16,2018", 2018, 6, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "Dec 16 2018", 2018, 12, 16
    },


    // MONTH DD,YYYY
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "february 16, 2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "february 16,2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "february 16 2018", 2018, 2, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "december 16, 2018", 2018, 12, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "MARCH 16,2018", 2018, 3, 16
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "APril 16 2018", 2018, 4, 16
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
    "2018-0-0",
    "2018-02-31",
    "2018-04-31",
    "1999-06-31",
    "2033-11-31",
    "1970-33-99",
    "1980-13-04",
    "2001-12-32",
    "cat",
    "",
    "feb 31, 2014",
    "jun 31, 1999"
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