#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <string>
#include <stdexcept>

namespace ai {
    class InvalidArgumentException: public std::runtime_error
    {
    public:
        explicit InvalidArgumentException(const std::string& message);
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
