#pragma once

#include <stdexcept>

class interpreterException : public std::logic_error
{
public:
    interpreterException(const std::string& msg)
        : logic_error(msg)
    {}
};