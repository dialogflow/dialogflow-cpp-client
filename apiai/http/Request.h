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
    Credentials credentials;
protected:
    HTTPRequest httpRequest;
    virtual T fromResponse(std::string response) = 0;
public:
    Request(Credentials credentials): credentials(credentials), httpRequest("https://api.api.ai/v1/query?v=20150910")
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
