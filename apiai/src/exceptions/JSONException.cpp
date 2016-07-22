#include <apiai/exceptions/JSONException.h>

#include <sstream>

namespace ai {

JSONException::JSONException(const std::string& message): std::runtime_error(message) {}

JSONException JSONException::MissingKey(const std::string &key)
{
    std::ostringstream reason;

    reason << "Missing key: ";
    reason << key;
    reason << ".";

    return JSONException(reason.str());
}

JSONException JSONException::TypeMismatch(const std::string &key, const std::string &expected_type)
{
    std::ostringstream reason;

    reason << "Type mismatch, key: ";
    reason << key;
    reason << ", expected type: ";
    reason << expected_type;
    reason << ".";

    return JSONException(reason.str());
}

}
