#include "AI.h"
#include <curl/curl.h>

#include <iostream>

namespace ai {
    std::shared_ptr<Credentials> AI::credentials = std::shared_ptr<Credentials>(nullptr);

    void AI::global_clean() {
        curl_global_cleanup();
    }

    void AI::global_init() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    void AI::configure(const Credentials &credentials) {
        AI::credentials = std::shared_ptr<Credentials>(new Credentials(credentials));
    }

    void AI::configure(const std::string &clientAccessToken, const std::string &subscribtionKey) {
        AI::configure(Credentials(clientAccessToken, subscribtionKey));
    }

    Service& AI::sharedService() {
        static std::once_flag once_flag;
        static std::shared_ptr<Service> service = nullptr;

        std::call_once(once_flag, [](){
            if (AI::credentials.get() == NULL) {
                exit(-1); //api should be configured with ::configure method(s)
            } else {
                service = std::shared_ptr<Service>(new Service(*AI::credentials));
            }
        });

        return *service;
    }
}
