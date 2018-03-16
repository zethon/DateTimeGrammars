#pragma once

#ifndef DATE_TIME_GRAMMAR_HPP
#define DATE_TIME_GRAMMAR_HPP

#include <QDateTime>
#include <boost/spirit/include/qi.hpp>

namespace bsq = boost::spirit::qi;
namespace bph = boost::phoenix;

namespace DateTimeGrammars
{

// stupid test function to build unit tests
bool isEven(unsigned int x)
{
    QTime time1 = QTime::fromString("131", "HHh");
    if (time1.isValid())
        return (x % 2) == 0;

    return 1;
}

// template<typename Iterator>
// struct EpochGrammar
//     : bsq::grammar<Iterator, typename Header<Iterator>::Type() >
// {

// };

}

#endif // DATE_TIME_GRAMMAR_HPP