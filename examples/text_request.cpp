/**
 * Copyright 2017 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

    auto credentials = ai::Credentials("09604c7f91ce4cd8a4ede55eb5340b9d");
//    auto credentials = ai::Credentials("Same wrong access key.");

    auto params = Parameters("<session id unique for every user>").setResetContexts(true);

    auto request = std::shared_ptr<TextQueryRequest>(new TextQueryRequest(QueryText::One("test context parameters"), "en", credentials, params));

    try {
        std::cout << request->perform() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

//    auto credentials = ai::Credentials("ff98c090685f484caaffada53cdce7b3", "4c91a8e5-275f-4bf0-8f94-befa78ef92cd");

//    auto params = Parameters("<session id unique for every user>")
//            .addEntity(
//                Entity("dwarfs")
//                    .addEntry(
//                        Entry("Ori").addSynonym("ori").addSynonym("Nori")
//                    ).addEntry(
//                        Entry("bifur").addSynonym("Bofur").addSynonym("Bombur")
//                    )
//            ).addContext(
//                RequestContext("context")
//            );

//    auto request = std::shared_ptr<TextQueryRequest>(new TextQueryRequest(QueryText::One("hi nori"), "en", credentials, params));

//    try {
//        auto response = request->perform();
//        std::cout << response << std::endl;
//    } catch(std::exception &e) {
//        std::cout << e.what() << std::endl;
//    }

    ai::AI::global_clean();

//#endif

    return 0;
}

//#undef CHECKS_STREAM_THREAD_SAFETY
