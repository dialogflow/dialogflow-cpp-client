#include <apiai/AI.h>
#include <curl/curl.h>

#include <iostream>
#include <sstream>

using namespace ai;
using namespace ai::query::request;

using namespace std;

std::shared_ptr<Credentials> AI::credentials = std::shared_ptr<Credentials>(nullptr);

std::shared_ptr<Parameters> AI::parameters = std::shared_ptr<Parameters>(nullptr);

void AI::global_clean()
{
    curl_global_cleanup();
}

void AI::global_init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

void AI::configure(const Credentials &credentials)
{
    AI::credentials = std::shared_ptr<Credentials>(new Credentials(credentials));
}

void AI::configure(const std::string &clientAccessToken, const std::string &subscribtionKey)
{
    AI::configure(clientAccessToken);
}

void AI::configure(const std::string &clientAccessToken)
{
    AI::configure(Credentials(clientAccessToken));
}

void AI::setupDefaultParameters(const Parameters& parameters)
{
    AI::parameters = shared_ptr<Parameters>(new Parameters(parameters));
}

Service& AI::sharedService() {
    static std::once_flag once_flag;
    static std::shared_ptr<Service> service = nullptr;

    std::call_once(once_flag, [](){
        if (AI::credentials.get() == nullptr || AI::parameters.get() == nullptr) {
            exit(-1);   // api should be configured with ::configure method(s)
                        // api should be configured with ::setupDefaultParameters method
        } else {
            service = std::shared_ptr<Service>(new Service(*AI::credentials, *AI::parameters));
        }
    });

    return *service;
}
