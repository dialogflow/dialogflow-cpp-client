#include <apiai/exceptions/Exception.h>

namespace ai {
    Exception::Exception(const char *reason) AI_NOEXCEPT: reason(reason) {

    }

    const char* Exception::what() const AI_NOEXCEPT {
        return reason.c_str();
    }

    Exception::~Exception() AI_NOEXCEPT {

    }
}
