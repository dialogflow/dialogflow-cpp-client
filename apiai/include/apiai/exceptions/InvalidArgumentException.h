#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <string>
#include <exception>
#include <stdexcept>

namespace ai {
    class InvalidArgumentException: public std::runtime_error
    {
    private:
//        std::string reason;
    public:
        InvalidArgumentException(const std::string &reason);

//        virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;

//        virtual ~InvalidArgumentException() _GLIBCXX_USE_NOEXCEPT;
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
