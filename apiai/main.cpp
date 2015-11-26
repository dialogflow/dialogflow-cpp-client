#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include <future>
#include <thread>

#include <curl/curl.h>
#include <cJSON.h>

#include "AI.h"

#include "query/Query.h"
#include "Exception.h"

#include "JSON/JSONException.h"

using namespace std;

int main(int argc, char *argv[]) {
    ai::AI::global_init();

    auto credentials = ai::Credentials("3485a96fb27744db83e78b8c4bc9e7b7", "cb9693af-85ce-4fbf-844a-5563722fc27f");

    ai::query::QueryRequest request("Hello", "en", credentials);

    auto response = request.perform();

//    std::cout << "identifier: " << response.result.getFulfillment()->getSpeech() << std::endl;

    std::cout << response << std::endl;

    ai::AI::global_clean();

    return 0;
}
