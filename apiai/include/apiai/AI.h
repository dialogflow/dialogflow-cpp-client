#ifndef AI_H
#define AI_H

#include "Credentials.h"
#include "Service.h"

#include <mutex>

namespace ai {
    class AI
    {
    private:
        static std::shared_ptr<Credentials> credentials;
    public:
        static void global_init();
        static void global_clean();

        static void configure(const Credentials &credentials);
        static void configure(const std::string &clientAccessToken, const std::string &subscribtionKey);

        static Service& sharedService();
    };
}

#endif // AI_H
