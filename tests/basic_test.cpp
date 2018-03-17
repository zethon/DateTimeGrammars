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

BOOST_AUTO_TEST_CASE(is_even_test)
{
    BOOST_CHECK(isEven(2));
    BOOST_CHECK(!isEven(3));
}

std::tuple<std::string, unsigned int, unsigned int, unsigned int> dateOnlyGoodData[] = 
{
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "2018-12-11", 2018, 12, 11
    },
    std::tuple<std::string, unsigned int, unsigned int, unsigned int>
    {
        "1969-07-20", 1969, 7, 20
    }    
};

BOOST_DATA_TEST_CASE(dateOnlyTest, data::make(dateOnlyGoodData), datestring, year, month, day)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    std::string::const_iterator begin = datestring.begin();
    std::string::const_iterator end = datestring.end();

    std::tuple<unsigned int, unsigned int, unsigned int> tp;
    bool didParse = boost::spirit::qi::parse(begin, end, parser, tp);

    BOOST_REQUIRE(didParse);
    BOOST_REQUIRE((begin == end));
    BOOST_REQUIRE((std::get<0>(tp) == year));
    BOOST_REQUIRE((std::get<1>(tp) == month));
    BOOST_REQUIRE((std::get<2>(tp) == day));

    std::cout << "TUPLE: " << tp << std::endl;
    std::cout << "DONE\n";     
}

BOOST_AUTO_TEST_CASE(foo_test)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    std::string date1 = "2018-12-11";
    std::string::const_iterator begin = date1.begin();
    std::string::const_iterator end = date1.end();

    std::tuple<unsigned int, unsigned int, unsigned int> tp;
    
    bool didParse = boost::spirit::qi::parse(begin, end, parser, tp);

    // BOOST_REQUIRE(didParse);
    // BOOST_REQUIRE((begin == end));

    std::cout << "TUPLE: " << tp << std::endl;
    std::cout << "DONE\n"; 
}

BOOST_AUTO_TEST_SUITE_END()