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
        InvalidArgumentException(const std::string &reason);

        virtual const char* what() const throw() override;

        virtual ~InvalidArgumentException() throw();
    };
}

#endif // INVALIDARGUMENTEXCEPTION_H
