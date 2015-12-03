#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include <future>
#include <thread>
#include <functional>

#include <curl/curl.h>
#include <cJSON.h>

#include "AI.h"

#include "query/TextQueryRequest.h"
#include "query/request/QueryText.h"
#include "Exception.h"

#include "JSON/JSONException.h"

using namespace std;

using namespace ai::query::request;

template<typename T>
class Req
{
public:
    virtual T foo() = 0;
};

class TextRequest: private Req<int> {
public:
    virtual int foo() override {
        return 1;
    };
};

#ifndef CHECK_STREAMS
    #define CHECK_STREAMS 1
#endif

#include "io/ThreadSafetyCheck.h"

int main(int argc, char *argv[]) {

#ifdef CHECK_STREAMS

    ai::io::ThreadSafetyCheck::check();

#else

    ai::AI::global_init();

//    vector<int>::value_type;
    auto q = TextRequest();


    auto credentials = ai::Credentials("ff98c090685f484caaffada53cdce7b3", "4c91a8e5-275f-4bf0-8f94-befa78ef92cd");

    auto params = Parameters("<session id unique for every user>")
            .addEntity(
                Entity("dwarfs")
                    .addEntry(
                        Entry("Ori").addSynonym("ori").addSynonym("Nori")
                    ).addEntry(
                        Entry("bifur").addSynonym("Bofur").addSynonym("Bombur")
                    )
            ).addContext(
                RequestContext("context")
            );

    auto request = std::shared_ptr<TextQueryRequest>(new TextQueryRequest(QueryText::One("hi nori"), "en", credentials, params));

    auto response = request->perform();

    std::cout << response << std::endl;

    ai::AI::global_clean();

#endif

    return 0;
}
