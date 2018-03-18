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

struct QDate_isValid_impl
{
    typedef bool result_type;

    bool operator()(const QDate& date)
        const
    {
        return date.isValid();
    }
};

template<typename Iterator>
struct DateParser : bsq::grammar<Iterator, QDate()>
{
    using UIntTriplet = std::tuple<unsigned int, unsigned int, unsigned int>;

    DateParser()
        : DateParser::base_type(_query)
    {
        namespace bsq = boost::spirit::qi;
        namespace bph = boost::phoenix;
        
        _daynum = digit2 >> bsq::eps(1 <= bsq::_val && bsq::_val <= 31);
        _monthnum = digit2 >> bsq::eps(1 <= bsq::_val && bsq::_val <= 12);
        _yearnum = (digit4 | digit2);

        _date = _yearnum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _monthnum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _daynum;

        _query = _date[
            bsq::_val = bph::construct<QDate>(
                    bph::at_c<0>(bsq::_1), 
                    bph::at_c<1>(bsq::_1), 
                    bph::at_c<2>(bsq::_1)
                ),
            bph::if_(!is_valid(bsq::_val))
                [
                   bsq::_pass = false
                ]
            ];
    }

    bsq::uint_parser<unsigned int, 10, 4, 4> digit4;
    bsq::uint_parser<unsigned int, 10, 1, 2> digit2;

    boost::spirit::qi::rule<Iterator, unsigned int()> _daynum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _monthnum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _yearnum;

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _date;
    boost::spirit::qi::rule<Iterator, QDate() > _query;

    static const boost::phoenix::function<QDate_isValid_impl> is_valid;
};

template <typename Iterator>
const boost::phoenix::function<QDate_isValid_impl> DateParser<Iterator>::is_valid;

}

#endif // DATE_TIME_GRAMMAR_HPP