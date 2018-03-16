#pragma once

#ifndef DATE_TIME_GRAMMAR_HPP
#define DATE_TIME_GRAMMAR_HPP

#include <boost/spirit/include/qi.hpp>

namespace DateTimeGrammars
{

// stupid test function to build unit tests
bool isEven(unsigned int x)
{
    return (x % 2) == 0;
}


}

#endif // DATE_TIME_GRAMMAR_HPP