#include <apiai/http/RequestConnection.h>
#include <apiai/Credentials.h>

#include "RequestConnectionImpl.h"

using namespace ai;

RequestConnection::RequestConnection(std::string URL): impl(new RequestConnectionImpl(URL))
{

}

void RequestConnection::authentificate(const Credentials& credentials)
{
    std::ostringstream authorization;

    authorization << "Bearer ";
    authorization << credentials.getClientAccessToken();

    impl->addHeader("Authorization", authorization.str());
}

std::string RequestConnection::performConnection()
{
    return impl->performConnection();
}

RequestConnection::~RequestConnection()
{

}
