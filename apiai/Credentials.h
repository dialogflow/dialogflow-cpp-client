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

        // TODO: It would be nice to decorate the constructor as shown below.
//        Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey);
        Credentials(std::string clientAccessToken, std::string subscribtionKey);

        // TODO: It would be nice to decorate the getters this way.
//        const std::string &getClientAccessToken() const;
//        const std::string &getSubscribtionKey() const;

        std::string getClientAccessToken() const;
        std::string getSubscribtionKey() const;
    };
}

#endif // CREDENTIALS_H
