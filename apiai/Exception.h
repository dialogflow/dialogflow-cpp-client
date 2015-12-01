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

    Exception(const char *reason) throw();

    virtual const char* what() const throw() override;

    virtual ~Exception() throw();
};

}
#endif // EXCEPTION_H
