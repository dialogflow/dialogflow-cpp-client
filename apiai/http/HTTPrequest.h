#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>

namespace ai {

class HTTPRequest
{
    class HTTPRequestImpl;
    std::unique_ptr<HTTPRequestImpl> impl;
public:
    // TODO: It would be nice to decorate the constructor as shown below.
//    HTTPRequest(const std::string &URL);
    HTTPRequest(std::string URL);

    // TODO: It would be nice to decorate the getter as shown below.
//    const std::string &getBody() const;
    std::string getBody() const;
    void setBody(const std::string &value);

    // TODO: It would be nice to decorate the getter as shown below.
//    std::string getURL() const;
    std::string getURL() const;
    void setURL(const std::string &value);

    // TODO: It would be nice to decorate the getter as shown below.
//    const std::map<std::string, std::string> &getHeaders() const;
    std::map<std::string, std::string> getHeaders() const;
    void setHeaders(const std::map<std::string, std::string> &value);

    // TODO: It would be nice to decorate the 'addHeader'-method as shown below.
//    HTTPRequest& addHeader(const std::string &name, const std::string &value);
    HTTPRequest& addHeader(std::string name, std::string value);

    std::string perform();

    virtual ~HTTPRequest();
};
}

#endif // HTTPREQUEST_H
