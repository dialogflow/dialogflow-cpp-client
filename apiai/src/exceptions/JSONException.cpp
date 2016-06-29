#include <apiai/exceptions/JSONException.h>

#include <sstream>

namespace ai {

JSONException::JSONException(const std::string &reason): reason(reason)
{

}

JSONException JSONException::MissingKey(const std::string &key) _NOEXCEPT
{
    std::ostringstream reason;

    reason << "Missing key: ";
    reason << key;
    reason << ".";

    return JSONException(reason.str());
}

JSONException JSONException::TypeMismatch(const std::string &key, const std::string &expected_type) _NOEXCEPT
{
    std::ostringstream reason;

    reason << "Type mismatch, key: ";
    reason << key;
    reason << ", expected type: ";
    reason << expected_type;
    reason << ".";

    return JSONException(reason.str());
}

const char* JSONException::what() const _NOEXCEPT
{
    return reason.c_str();
}

JSONException::~JSONException() _NOEXCEPT
{

}


}
