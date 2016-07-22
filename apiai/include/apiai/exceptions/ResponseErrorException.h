#ifndef RESPONSEERROREXCEPTION_H
#define RESPONSEERROREXCEPTION_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

namespace ai {
    class ResponseErrorException: public std::runtime_error
    {
    private:
        const std::string errorType;
        const std::string errorDetails;
        const int code;
    public:
        explicit ResponseErrorException(const std::string &errorType, const std::string &errorDetails, const int &code);

        inline int getCode() const
        {
            return code;
        }

        inline std::string getErrorType() const
        {
            return errorType;
        }

        inline std::string getErrorDetails() const
        {
            return errorDetails;
        }
    };
}


#endif // RESPONSEERROREXCEPTION_H
