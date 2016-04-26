#include <apiai/Credentials.h>

namespace ai {

PUSH_DEPRECATED_WARNING()

    const std::string &Credentials::getClientAccessToken() const
    {
        return clientAccessToken;
    }

    const std::string &Credentials::getSubscribtionKey() const
    {
        return subscribtionKey;
    }

    Credentials::Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey):
        clientAccessToken(clientAccessToken)
    {
        this->subscribtionKey = subscribtionKey;
    }

    Credentials::Credentials(const std::string &clientAccessToken):
        clientAccessToken(clientAccessToken)
    {
        this->subscribtionKey = "";
    }

    Credentials::Credentials(const Credentials &credentials) {
        this->clientAccessToken = credentials.clientAccessToken;
        this->subscribtionKey = credentials.subscribtionKey;
    }

    Credentials::~Credentials() {

    }

POP_DEPRECATED_WARNING()
}
