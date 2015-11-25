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
    JSONException(std::string reason);

    static JSONException MissingKey(std::string key) throw();
    static JSONException TypeMismatch(std::string key, std::string expected_type) throw();

    virtual const char* what() const throw() override;

    virtual ~JSONException() throw();
};


}
#endif // JSONEXCEPTION_H
