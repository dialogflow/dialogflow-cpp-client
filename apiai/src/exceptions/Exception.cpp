#include <apiai/exceptions/Exception.h>

namespace ai {
    Exception::Exception(const char *reason) _GLIBCXX_USE_NOEXCEPT: reason(reason) {

    }

    const char* Exception::what() const _GLIBCXX_USE_NOEXCEPT {
        return reason.c_str();
    }

    Exception::~Exception() _GLIBCXX_USE_NOEXCEPT {

    }
}
