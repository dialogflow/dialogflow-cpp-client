#include <apiai/http/RequestConnection.h>

#include "RequestConnectionImpl.h"

using namespace ai;

RequestConnection::RequestConnection(std::string URL): impl(new RequestConnectionImpl(URL))
{

}

std::string RequestConnection::performConnection()
{
    return impl->performConnection();
}

RequestConnection::~RequestConnection()
{

}
