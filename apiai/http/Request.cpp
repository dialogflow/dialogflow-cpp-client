#include "Request.h"

#include <curl/curl.h>
#include <exception>
#include <string>
#include <sstream>

#include "../Exception.h"
#include "HTTPRequest.h"


namespace ai {

//template <typename T>
//Request<T>::Request(Credentials credentials): credentials(credentials), httpRequest("https://api.api.ai/v1/query")
//{
//    std::ostringstream authorization;

//    authorization << "Bearer ";
//    authorization << credentials.getClientAccessToken();

//    httpRequest.
//            addHeader("Authorization", authorization.str())
//            .addHeader("ocp-apim-subscription-key", credentials.getSubscribtionKey());
//}

//template <typename T>
//T Request<T>::perform() {
//    auto response = httpRequest.perform();
//    return this->fromResponse(response);
//}

//template <typename T>
//Request<T>::~Request()
//{

//}

}

