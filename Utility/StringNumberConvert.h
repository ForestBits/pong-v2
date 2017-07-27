//convertgs strings to numbers and vice versa

#ifndef STRINGNUMBERCONVERT_H
#define STRINGNUMBERCONVERT_H

#include <sstream>

namespace pong {

template <typename T>
std::string toString(T number)
{
    std::stringstream stream;

    stream << number;

    return stream.str();
}

template <typename T = int>
T toNumber(const std::string & string)
{
    std::stringstream stream(string);

    T number;

    stream >> number;

    return number;
}

}

#endif