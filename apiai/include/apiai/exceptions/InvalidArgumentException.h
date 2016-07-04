#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <string>
#include <exception>
#include <stdexcept>

#include "Noexcept.h"

namespace ai {
    class InvalidArgumentException: public std::exception
    {
    private:
        std::string reason;
    public:
        InvalidArgumentException(const std::string &reason): reason(reason) {}

        const char *what () const AI_NOEXCEPT {
            return reason.c_str();
        }

        ~InvalidArgumentException() AI_NOEXCEPT {}
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
