#include <apiai/exceptions/InvalidArgumentException.h>

using namespace ai;

InvalidArgumentException::InvalidArgumentException(const std::string &reason) _GLIBCXX_USE_NOEXCEPT: reason(reason)
{

}

const char* InvalidArgumentException::what() const _GLIBCXX_USE_NOEXCEPT
{
    return reason.c_str();
}

InvalidArgumentException::~InvalidArgumentException() _GLIBCXX_USE_NOEXCEPT
{

}
