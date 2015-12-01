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
    // TODO: It would be nice to decorate the constructor as shown below.
//    JSONException(const std::string &reason);
    JSONException(std::string reason);

    // TODO: It would be nice to decorate the convenience methods as shown below.
//    static JSONException MissingKey(const std::string &key) throw();
//    static JSONException TypeMismatch(const std::string &key, const std::string &expected_type) throw();
    static JSONException MissingKey(std::string key) throw();
    static JSONException TypeMismatch(std::string key, std::string expected_type) throw();

    virtual const char* what() const throw() override;

    virtual ~JSONException() throw();
};


}
#endif // JSONEXCEPTION_H
