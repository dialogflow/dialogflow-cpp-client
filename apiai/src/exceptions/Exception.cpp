#include <apiai/exceptions/Exception.h>

namespace ai {
    Exception::Exception(const char *reason) _NOEXCEPT: reason(reason) {

    }

    const char* Exception::what() const _NOEXCEPT {
        return reason.c_str();
    }

    Exception::~Exception() _NOEXCEPT {

    }
}
