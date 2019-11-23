#pragma once

#ifndef DATE_TIME_GRAMMAR_HPP
#define DATE_TIME_GRAMMAR_HPP

#include <QDate>
#include <QDebug>
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

struct QTime_isValid_impl
{
    typedef bool result_type;

    bool operator()(const QTime& time)
        const
    {
        return time.isValid();
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

        months.add
            ("january",1) ("february",2) ("march",3) ("april",4)
            ("may",5) ("june",6) ("july",7) ("august",8)
            ("september",9) ("october",10) ("november",11) ("december",12);

        monthsabbr.add
            ("jan", 1) ("feb", 2) ("mar", 3) ("apr", 4)
            ("may", 5) ("jun", 6) ("jul", 7) ("aug", 8)
            ("sep", 9) ("oct", 10) ("nov", 11) ("dec", 12);
        
        _daynum = digit2 >> bsq::eps(1 <= bsq::_val && bsq::_val <= 31);
        _monthnum = digit2 >> bsq::eps(1 <= bsq::_val && bsq::_val <= 12);
        _yearnum = digit4;

        _dateYMD = _yearnum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _monthnum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _daynum;

        _dateDMY = _daynum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _monthnum
            >> (bsq::lit('-') | bsq::lit('/'))
            >> _yearnum;

        _qDMY = _dateDMY[
            bsq::_val = bph::construct<QDate>(
                    bph::at_c<2>(bsq::_1), 
                    bph::at_c<1>(bsq::_1), 
                    bph::at_c<0>(bsq::_1)
                ),
                bsq::_pass = is_valid(bsq::_val)
            ];

        _qYMD = _dateYMD[
            bsq::_val = bph::construct<QDate>(
                    bph::at_c<0>(bsq::_1), 
                    bph::at_c<1>(bsq::_1), 
                    bph::at_c<2>(bsq::_1)
                ),
                bsq::_pass = is_valid(bsq::_val)
            ];

        _monMDY = bsq::no_case[(months | monthsabbr)]
            >> bsq::lit(' ')
            >> _daynum
            >> (bsq::lit(", ") | bsq::lit(',') | bsq::lit(' '))
            >> _yearnum;

        _qmonMDY = _monMDY[
            bsq::_val = bph::construct<QDate>(
                bph::at_c<2>(bsq::_1),
                bph::at_c<0>(bsq::_1),
                bph::at_c<1>(bsq::_1)
                ),
             bsq::_pass = is_valid(bsq::_val)
            ];

        _query = (_qmonMDY | _qYMD | _qDMY);
    }

    bsq::uint_parser<unsigned int, 10, 4, 4> digit4;
    bsq::uint_parser<unsigned int, 10, 1, 2> digit2;

    boost::spirit::qi::rule<Iterator, unsigned int()> _daynum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _monthnum;
    boost::spirit::qi::rule<Iterator, unsigned int()> _yearnum;

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _dateYMD;
    boost::spirit::qi::rule<Iterator, QDate()> _qYMD;

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _dateDMY;
    boost::spirit::qi::rule<Iterator, QDate()> _qDMY;

    boost::spirit::qi::rule<Iterator, UIntTriplet()> _monMDY;
    boost::spirit::qi::rule<Iterator, QDate()> _qmonMDY;
    
    boost::spirit::qi::rule<Iterator, QDate()> _query;

    boost::spirit::qi::symbols<char, int>  months;
    boost::spirit::qi::symbols<char, int>  monthsabbr;

    static const boost::phoenix::function<QDate_isValid_impl> is_valid;
};

template<typename Iterator>
struct TimeParser : bsq::grammar<Iterator, QTime()>
{
    using UIntPair = std::tuple<unsigned int, unsigned int>;

    TimeParser()
        : TimeParser::base_type(_query)
    {
        namespace bsq = boost::spirit::qi;
        namespace bph = boost::phoenix;

        _hourdigit = digit2 >> bsq::eps(0 <= bsq::_val && bsq::_val <= 24);
        _minutedigit = digit2 >> bsq::eps(0 <= bsq::_val && bsq::_val <= 59);
    }

    bsq::uint_parser<unsigned int, 10, 1, 2> _hourdigit;
    bsq::uint_parser<unsigned int, 10, 1, 2> _minutedigit;
    bsq::uint_parser<unsigned int, 10, 1, 2> digit2;

    boost::spirit::qi::rule<Iterator, QDate()> _query;

    static const boost::phoenix::function<QTime_isValid_impl> is_valid;
};

template <typename Iterator>
const boost::phoenix::function<QDate_isValid_impl> DateParser<Iterator>::is_valid;

template <typename Iterator>
const boost::phoenix::function<QTime_isValid_impl> TimeParser<Iterator>::is_valid;
}

#endif // DATE_TIME_GRAMMAR_HPP