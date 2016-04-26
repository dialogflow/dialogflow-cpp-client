#ifndef RESPONSEERROREXCEPTION_H
#define RESPONSEERROREXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <memory>

namespace ai {
    class ResponseErrorException: public std::exception
    {
    private:
        const std::string errorType;
        const std::string errorDetails;
        const int code;
    public:
        ResponseErrorException(const std::string &errorType, const std::string &errorDetails, const int &code): errorType(errorType), errorDetails(errorDetails), code(code)
        {

        }

        virtual const char *what () const _GLIBCXX_USE_NOEXCEPT override
        {
            return errorDetails.c_str();
        }

        ~ResponseErrorException() _GLIBCXX_USE_NOEXCEPT
        {

        }

        int getCode() const
        {
            return code;
        }

        std::string getErrorType() const
        {
            return errorType;
        }

        std::string getErrorDetails() const
        {
            return errorDetails;
        }
    };
}


#endif // RESPONSEERROREXCEPTION_H
