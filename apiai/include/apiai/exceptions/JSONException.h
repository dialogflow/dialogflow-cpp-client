#ifndef JSONEXCEPTION_H
#define JSONEXCEPTION_H

#include <exception>
#include <string>

namespace ai {

class JSONException: public std::exception
{
private:
    std::string reason;
public:
    JSONException(const std::string &reason);

    static JSONException MissingKey(const std::string &key) _GLIBCXX_USE_NOEXCEPT;
    static JSONException TypeMismatch(const std::string &key, const std::string &expected_type) _GLIBCXX_USE_NOEXCEPT;

    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override;

    virtual ~JSONException() _GLIBCXX_USE_NOEXCEPT;
};


}
#endif // JSONEXCEPTION_H
