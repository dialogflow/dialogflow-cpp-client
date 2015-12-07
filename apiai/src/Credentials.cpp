#include <apiai/Credentials.h>

namespace ai {
    const std::string &Credentials::getClientAccessToken() const
    {
        return clientAccessToken;
    }

    const std::string &Credentials::getSubscribtionKey() const
    {
        return subscribtionKey;
    }

    Credentials::Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey):
        clientAccessToken(clientAccessToken),
        subscribtionKey(subscribtionKey)
    {

    }
}
