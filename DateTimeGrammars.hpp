#pragma once

#ifndef DATE_TIME_GRAMMAR_HPP
#define DATE_TIME_GRAMMAR_HPP

#include <QDate>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>

namespace bsq = boost::spirit::qi;
namespace bph = boost::phoenix;

namespace DateTimeGrammars
{

// stupid test function to build unit tests
bool isEven(unsigned int x)
{
    return (x % 2) == 0;
}

template<typename Iterator>
struct DateParser : bsq::grammar<Iterator, QDate()>
{
    DateParser()
        : DateParser::base_type(_start)
    {
        using boost::phoenix::at_c;
        using boost::spirit::qi::_1;
        using boost::spirit::qi::_val;

        _start = _date[at_c<2>(_val), at_c<1>(_val), at_c<0>(_val)];
        
        _date = bsq::uint_parser<unsigned int, 10, 2, 4>()
            >> ('-' | '/')
            >> bsq::uint_parser<unsigned int, 10, 1, 2>()
            >> ('-' | '/')
            >> bsq::uint_parser<unsigned int, 10, 1, 2>();
    }

    boost::spirit::qi::rule<Iterator, std::tuple<int, int, int>()> _date;
    boost::spirit::qi::rule<Iterator, QDate() > _start;
};

}

#endif // DATE_TIME_GRAMMAR_HPP