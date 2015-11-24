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

using namespace std;

//class Headers {
//private:
//    Headers(const Headers& headers) {}

//    std::map<std::string, std::string> headers;
//    struct curl_slist *curl_headers;

//    struct curl_slist * buildCurlHeaders() {
//        if (!curl_headers) {
//            struct curl_slist *chunk = NULL;

//            for (auto &key_value :headers) {
//                auto header = std::ostringstream();
//                header << key_value.first << ": " << key_value.second;

//                chunk = curl_slist_append(chunk, header.str().c_str());
//            }

//            curl_headers = chunk;
//        }

//        return curl_headers;
//    }
//public:
//    Headers(): curl_headers(nullptr) {}
//    virtual ~Headers() {
//        if (curl_headers) {
//            curl_slist_free_all(curl_headers);
//            curl_headers = nullptr;
//        }
//    }

//    Headers& add_header(std::string name, std::string value) {
//        if (curl_headers) {
//            curl_slist_free_all(curl_headers);
//            curl_headers = nullptr;
//        }

//        headers[name] = value;
//        return *this;
//    }

//    Headers& remove_header(std::string name) {
//        if (curl_headers) {
//            curl_slist_free_all(curl_headers);
//            curl_headers = nullptr;
//        }

//        headers.erase(name);
//        return *this;
//    }

//    friend class Request;
//};

//class Upload {
//public:
//    std::string data;
//    int offset;

//    Upload(std::string data): data(data), offset(0) {}
//};

//uint write_callback(char *in, uint size, uint nmemb, std::string *response)
//{
//  uint r = size * nmemb;

//  response->append(in);

//  return r;
//}

//static size_t read_callback(void *ptr, size_t size, size_t nmemb, Upload *upload)
//{
//    auto total_memory = size * nmemb;

//    auto avaiable = std::min(total_memory, upload->data.size() - upload->offset);

//    if (avaiable > 0) {
//        memcpy(ptr, upload->data.c_str() + upload->offset, avaiable);
//        upload->offset += avaiable;

//        return avaiable;
//    }

//    return 0; //CURL_READFUNC_ABORT
//}

//class Request
//{
//protected:
//    CURL *curl;
//    Headers headers;
//    std::string URL;
//public:
//    Request(){
//        URL = "https://api.api.ai/v1/query?v=20150910";
//        curl = curl_easy_init();

//        headers.add_header("Content-Type", "application/json");
//        headers.add_header("Transfer-Encoding", "chunked");
//    }

//    virtual ~Request(){
//        curl_easy_cleanup(curl);
//    }

//    void perform() {
////        std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
//        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

//        curl_easy_setopt(curl, CURLOPT_POST, 1L);
////        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

////        curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

//        auto curl_headers = headers.buildCurlHeaders();

//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);

//        auto request = std::string(
//                    "{\"query\": \"Hello\", \"lang\": \"en\"}"
//                    );

//        auto upload = Upload(request);

//        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
//        curl_easy_setopt(curl, CURLOPT_READDATA, &upload);

//        auto response = std::string();
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

//        CURLcode res = curl_easy_perform(curl);

//        std::cout << response << std::endl;
//    }
    
//    void authentificate(ai::Credentials credentials) {
//        auto authorization = std::ostringstream();

//        authorization << "Bearer " << credentials.getClientAccessToken();

//        this->headers
//                .add_header("Authorization", authorization.str())
//                .add_header("ocp-apim-subscription-key", credentials.getSubscribtionKey());
//    }
//};

int main(int argc, char *argv[]) {
    ai::AI::global_init();

    auto credentials = ai::Credentials("3485a96fb27744db83e78b8c4bc9e7b7", "cb9693af-85ce-4fbf-844a-5563722fc27f");

//    auto request = Request();
//    request.authentificate(credentials);

//    ai::AI::configure("1", "2");

//    request.perform();

//    auto request = ai::Query::QueryRequest(credentials);
     ai::Query::QueryRequest request(credentials);

    ai::AI::global_clean();

    try {
        throw ai::Exception("Some reason.");
    } catch (std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}
