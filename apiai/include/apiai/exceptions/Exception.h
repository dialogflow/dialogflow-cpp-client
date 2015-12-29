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

    Exception(const char *reason) _GLIBCXX_USE_NOEXCEPT;

    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override;

    virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;
};

}
#endif // EXCEPTION_H
