#ifndef INVALIDARGUMENTEXCEPTION_H
#define INVALIDARGUMENTEXCEPTION_H

#include <string>
#include <exception>

namespace ai {
    class InvalidArgumentException: public std::exception
    {
    private:
        std::string reason;
    public:
        InvalidArgumentException(const std::string &reason) _GLIBCXX_USE_NOEXCEPT;

        virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override;

        virtual ~InvalidArgumentException() _GLIBCXX_USE_NOEXCEPT;
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
