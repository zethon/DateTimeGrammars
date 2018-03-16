#pragma once

#ifndef DATE_TIME_GRAMMAR_HPP
#define DATE_TIME_GRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>

namespace bsq = boost::spirit::qi;
namespace bph = boost::phoenix;

namespace DateTimeGrammars
{

// stupid test function to build unit tests
bool isEven(unsigned int x)
{
    return (x % 2) == 0;
}

// template<typename Iterator>
// struct EpochGrammar
//     : bsq::grammar<Iterator, typename Header<Iterator>::Type() >
// {

// };

}

#endif // DATE_TIME_GRAMMAR_HPP