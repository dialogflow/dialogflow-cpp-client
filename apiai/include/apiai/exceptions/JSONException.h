#ifndef JSONEXCEPTION_H
#define JSONEXCEPTION_H

#include <exception>
#include <string>

#include "Noexcept.h"

namespace ai {

class JSONException: public std::exception
{
private:
    std::string reason;
public:
    JSONException(const std::string &reason);

    static JSONException MissingKey(const std::string &key) AI_NOEXCEPT;
    static JSONException TypeMismatch(const std::string &key, const std::string &expected_type) AI_NOEXCEPT;

    virtual const char* what() const AI_NOEXCEPT override;

    virtual ~JSONException() AI_NOEXCEPT;
};


}
#endif // JSONEXCEPTION_H
