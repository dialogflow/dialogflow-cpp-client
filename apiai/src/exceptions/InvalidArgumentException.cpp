#include <apiai/exceptions/InvalidArgumentException.h>

using namespace ai;

InvalidArgumentException::InvalidArgumentException(const std::string &reason): reason(reason)
{

}

const char* InvalidArgumentException::what() const throw()
{
    return reason.c_str();
}

InvalidArgumentException::~InvalidArgumentException() throw()
{

}
