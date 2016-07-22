#ifndef JSONEXCEPTION_H
#define JSONEXCEPTION_H

#include <string>
#include <stdexcept>

namespace ai {

class JSONException: public std::runtime_error
{
public:
    explicit JSONException(const std::string& message);

    static JSONException MissingKey(const std::string &key);
    static JSONException TypeMismatch(const std::string &key, const std::string &expected_type);
};


}
#endif // JSONEXCEPTION_H
