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
        Credentials(std::string clientAccessToken, std::string subscribtionKey);

        std::string getClientAccessToken() const;
        std::string getSubscribtionKey() const;
    };
}

#endif // CREDENTIALS_H
