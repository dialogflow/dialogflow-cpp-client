#include "Exception.h"

namespace ai {
    Exception::Exception(const char *reason) throw(): reason(reason) {

    }

    const char* Exception::what() const throw() {
        return reason.c_str();
    }

    Exception::~Exception() throw() {

    }
}
