#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <string>
#include <exception>
#include <stdexcept>

namespace ai {
    class InvalidArgumentException: public std::exception
    {
    private:
        std::string reason;
    public:
        InvalidArgumentException(const std::string &reason): reason(reason) {}

        const char *what () const _NOEXCEPT {
            return reason.c_str();
        }

        ~InvalidArgumentException() _NOEXCEPT {}
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
