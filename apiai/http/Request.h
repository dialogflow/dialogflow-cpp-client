#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <future>
#include <sstream>

#include "../Credentials.h"
#include "HTTPrequest.h"


namespace ai {
template <typename T> class Request
{
private:
    Request(const Request&);
    // TODO: It's also necessary to disallow assignment. It's better use DISALLOW_COPY_AND_ASSIGN by Google.
    Credentials credentials; // TODO: Is it necessary to keep credentials?
protected:
    HTTPRequest httpRequest;
    // TODO: It would be nice to decorate the 'fromResponse'-method as shown below.
    virtual T fromResponse(std::string response) = 0;
//    virtual T fromResponse(const std::string &response) = 0;
public:
    Request(Credentials/* TODO: Insert const & ? */credentials): credentials(credentials), httpRequest("https://api.api.ai/v1/query?v=20150910")
    {
        std::ostringstream authorization;

        authorization << "Bearer ";
        authorization << credentials.getClientAccessToken();

        httpRequest.
                addHeader("Authorization", authorization.str())
                .addHeader("ocp-apim-subscription-key", credentials.getSubscribtionKey());
    }

    virtual T perform() {
        auto response = httpRequest.perform();
        return this->fromResponse(response);
    }

    virtual ~Request() {}
};
}

//#include "Request.cpp"

#endif // REQUEST_H
