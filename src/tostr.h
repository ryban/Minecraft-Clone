// This class will convert any number into a string
#ifndef TOSTR_H
#define TOSTR_H

#include <sstream>

std::string toString(short s)
{
	std::ostringstream buff;
    buff << s;
    return buff.str();
}
std::string toString(int i)
{
    std::ostringstream buff;
    buff << i;
    return buff.str();
}
std::string toString(long l)
{
    std::ostringstream buff;
    buff << l;
    return buff.str();
}
std::string toString(float f)
{
    std::ostringstream buff;
    buff << f;
    return buff.str();
}
std::string toString(double d)
{
    std::ostringstream buff;
    buff << d;
    return buff.str();
}
#endif