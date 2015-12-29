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
        InvalidArgumentException(const std::string &reason);

        const char *what () const _GLIBCXX_USE_NOEXCEPT;

        ~InvalidArgumentException() _GLIBCXX_USE_NOEXCEPT;
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
