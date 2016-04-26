#ifndef AI_H
#define AI_H

#include "Credentials.h"
#include "Service.h"
#include "common/Deprecated.h"

#include <mutex>

namespace ai {
    class Credentials;
    namespace query {
        namespace request {
            class Parameters;
        }
    }

    class AI
    {
    private:
        static std::shared_ptr<Credentials> credentials;
        static std::shared_ptr<query::request::Parameters> parameters;
    public:
        static void global_init();
        static void global_clean();

        static void setupDefaultParameters(const query::request::Parameters& parameters);

        static void configure(const Credentials &credentials);
        DEPRECATED static void configure(const std::string &clientAccessToken, const std::string &subscribtionKey);

        static void configure(const std::string &clientAccessToken);

        static Service& sharedService();
    };
}

#endif // AI_H
