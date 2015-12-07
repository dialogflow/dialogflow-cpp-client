#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include <future>
#include <thread>
#include <functional>

#include <io/StreamReader.h>

#include <apiai/AI.h>

#include <apiai/query/TextQueryRequest.h>
#include <apiai/query/request/QueryText.h>
#include <apiai/exceptions/Exception.h>

#include <apiai/exceptions/JSONException.h>


using namespace std;

using namespace ai::query::request;

//#ifndef CHECKS_STREAM_THREAD_SAFETY

//#include "io/tests/StreamThreadSafetyCheck.h"
////    #define CHECKS_STREAM_THREAD_SAFETY 1
//#endif

int main(int argc, char *argv[]) {

//#ifdef CHECKS_STREAM_THREAD_SAFETY

//    ai::io::StreamThreadSafetyCheck::startChecking();

//#else

    ai::AI::global_init();

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

//#endif

    return 0;
}

//#undef CHECKS_STREAM_THREAD_SAFETY
