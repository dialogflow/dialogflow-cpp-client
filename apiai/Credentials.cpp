#include "Credentials.h"

namespace ai {
    std::string Credentials::getClientAccessToken() const
    {
        return clientAccessToken;
    }

    std::string Credentials::getSubscribtionKey() const
    {
        return subscribtionKey;
    }

    Credentials::Credentials(std::string clientAccessToken, std::string subscribtionKey):
        clientAccessToken(clientAccessToken),
        subscribtionKey(subscribtionKey)
    {

    }
}
