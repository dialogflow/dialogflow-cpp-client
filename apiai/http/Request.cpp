#include "Request.h"

#include <curl/curl.h>
#include <exception>

#include "../Exception.h"



namespace ai {

class Request::RequestImpl {
private:
    class Upload {
    public:
        std::string data;
        int offset;

        Upload(std::string data): data(data), offset(0) {}
    };

    CURL *curl;
    std::string body;
public:
    RequestImpl(){
        curl = curl_easy_init();
        if (!curl) {
            throw Exception("Cannot init CURL object.");
        }
    }

    void setBody(std::string body) {
        this->body = body;
    }

    void setURL(std::string URL) {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    }

    static size_t read_callback(void *ptr, size_t size, size_t nmemb, Upload *upload)
    {
        auto total_memory = size * nmemb;

        auto avaiable = std::min(total_memory, upload->data.size() - upload->offset);

        if (avaiable > 0) {
            memcpy(ptr, upload->data.c_str() + upload->offset, avaiable);
            upload->offset += avaiable;

            return avaiable;
        }

        return 0; //CURL_READFUNC_ABORT
    }

    static uint write_callback(char *in, uint size, uint nmemb, std::string *response)
    {
      uint r = size * nmemb;

      response->append(in);

      return r;
    }

    void perform() {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        auto upload = Upload(body);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload);

        auto response = std::string();

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode perform_result = curl_easy_perform(curl);
    }

    virtual ~RequestImpl(){
        curl_easy_cleanup(curl);
    }
};

Request::Request(Credentials credentials): credentials(credentials), impl(new RequestImpl())
{

}

void Request::perform() {
    impl->perform();
}

std::future<int> Request::async_perform()
{
    auto f = std::async(std::launch::async, [this](){
        this->perform();
        return 1;
    });

    return f;
}

Request::~Request()
{

}

}

