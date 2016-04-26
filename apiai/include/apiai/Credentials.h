#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <string>

#include "apiai/common/Deprecated.h"

namespace ai {
    class Credentials
    {
    private:
        std::string clientAccessToken;
        DEPRECATED std::string subscribtionKey;
    public:

        DEPRECATED Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey);

        Credentials(const std::string &clientAccessToken);

        const std::string &getClientAccessToken() const;
        DEPRECATED const std::string &getSubscribtionKey() const;

        Credentials(const Credentials &credentials);
        ~Credentials();
    };
}

#endif // CREDENTIALS_H
