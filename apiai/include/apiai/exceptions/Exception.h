#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

namespace ai {

class Exception: public std::exception
{
private:
    std::string reason;
public:

    Exception(const char *reason) _NOEXCEPT;

    virtual const char* what() const _NOEXCEPT override;

    virtual ~Exception() _NOEXCEPT;
};

}
#endif // EXCEPTION_H
