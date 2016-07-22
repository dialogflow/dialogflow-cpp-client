#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <stdexcept>

namespace ai {

class Exception: public std::runtime_error
{
public:
    explicit Exception(const std::string& message);
};

}
#endif // EXCEPTION_H
