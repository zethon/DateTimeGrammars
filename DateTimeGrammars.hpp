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

using UIntTriplet = std::tuple<unsigned int, unsigned int, unsigned int>;

template<typename Iterator>
struct DateParser : bsq::grammar<Iterator, UIntTriplet()>
{
    DateParser()
        : DateParser::base_type(_date)
    {
        namespace bsq = boost::spirit::qi;
        namespace bsp = boost::phoenix;

        _daynum = digit2;// >> bsq::eps(bsq::_val <= 31);
        _monthnum = digit2; // >> bsq::eps(bsq::_val <= 11);
        _yearnum = (digit4 | digit2);

        // _date = _yearnum //[bsq::labels::_a  = bsq::_1]
        //     >> '-'
        //     >> _monthnum //[bsq::labels::_b  = _1]
        //     >> '-'
        //     >> _daynum //[bsq::labels::_c  = _1]
        //     ;

        _date = _yearnum
            >> '-'
            >> bsq::uint_parser<unsigned int>()
            >> '-'
            >> bsq::uint_parser<unsigned int>();

        // _query = _date[_val = ]


        // // _start = _date[at_c<2>(_val), at_c<1>(_val), at_c<0>(_val)];
        // _start = eps[_val=construct<QDate>(at_c<2>(_val), at_c<1>(_val), at_c<0>(_val))];
        
        // _date = 
        //         bsq::uint_parser<unsigned int, 10, 2, 4>()[labels::_a = _1]
        //      >> ('-' | '/')
        //      >> bsq::uint_parser<unsigned int, 10, 1, 2>()[labels::_b = _1]
        //      >> ('-' | '/')
        //      >> bsq::uint_parser<unsigned int, 10, 1, 2>()[labels::_c = _1];
    }

    bsq::uint_parser<unsigned int, 10, 4, 4> digit4;
    bsq::uint_parser<unsigned int, 10, 1, 2> digit2;

    boost::spirit::qi::rule<Iterator, unsigned int()> _daynum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _monthnum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _yearnum;

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _date;
    // boost::spirit::qi::rule<Iterator, QDate() > _query;
};

}

#endif // DATE_TIME_GRAMMAR_HPP