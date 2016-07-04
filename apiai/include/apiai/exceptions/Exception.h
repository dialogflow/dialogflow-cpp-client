#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

#include "Noexcept.h"

namespace ai {

class Exception: public std::exception
{
private:
    std::string reason;
public:

    Exception(const char *reason) AI_NOEXCEPT;

    virtual const char* what() const AI_NOEXCEPT override;

    virtual ~Exception() AI_NOEXCEPT;
};

}
#endif // EXCEPTION_H
