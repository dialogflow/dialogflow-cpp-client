#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>

namespace ai {
    class Credentials
    {
    private:
        std::string clientAccessToken;
        std::string subscribtionKey;
    public:

        Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey);

        const std::string &getClientAccessToken() const;
        const std::string &getSubscribtionKey() const;
    };
}

#endif // CREDENTIALS_H
