#define BOOST_TEST_MAIN

#include "DateTimeGrammars.hpp"

#include <QDateTime>
#include <boost/test/unit_test.hpp>
#include <boost/fusion/adapted/std_tuple.hpp> 

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

// BOOST_AUTO_TEST_CASE(date_only_test)
// {
//     using string_it = std::string::const_iterator;
//     const DateParser<string_it> parser;

//     QDate parsed;
//     std::string date1 = "2018-12-01";

//     std::string::const_iterator begin = date1.begin();
//     std::string::const_iterator end = date1.end();

//     bool didParse = boost::spirit::qi::parse(begin, end, parser, parsed);
//     BOOST_CHECK(didParse);
//     BOOST_CHECK((begin == end));    
// }

BOOST_AUTO_TEST_CASE(foo_test)
{
    using string_it = std::string::const_iterator;
    const DateParser<string_it> parser;

    std::string date1 = "2018-12-11";
    std::string::const_iterator begin = date1.begin();
    std::string::const_iterator end = date1.end();

    std::tuple<unsigned int, unsigned int, unsigned int> tp;
    
    std::cout << "BEFORE: " << std::string(begin, end) << std::endl;
    bool didParse = boost::spirit::qi::parse(begin, end, parser, tp);
    std::cout << "END   : " << std::string(begin, end) << std::endl;


    // BOOST_REQUIRE(didParse);
    // BOOST_REQUIRE((begin == end));

    std::cout << "TUPLE: " << tp << std::endl;
    std::cout << "DONE\n"; 
}

BOOST_AUTO_TEST_SUITE_END()