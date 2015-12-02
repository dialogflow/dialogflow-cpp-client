#include "HTTPrequest.h"

#include <iostream>
#include <sstream>

#include <curl/curl.h>
#include "../Exception.h"

namespace ai {

class HTTPRequest::HTTPRequestImpl {
private:
    class Upload {
    public:
        std::string data;
        int offset;

        Upload(std::string data): data(data), offset(0) {}
    };

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
      response->append(in, size * nmemb);
      return size * nmemb;
    }

    CURL *curl;
    std::string body;
    std::string URL;

    std::map<std::string, std::string> headers;
public:
    HTTPRequestImpl(std::string URL):URL(URL) {
        curl = curl_easy_init();
        if (!curl) {
            throw Exception("Cannot init CURL object.");
        }

        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    }

    std::string getURL() const
    {
        return URL;
    }

    void setURL(const std::string &value)
    {
        URL = value;
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    }

    std::string getBody() const
    {
        return body;
    }

    void setBody(const std::string &value)
    {
        body = value;
    }

    std::string perform() {
        auto upload = Upload(body);

        if (body.length() > 0) {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
            curl_easy_setopt(curl, CURLOPT_READDATA, &upload);
        }

//        curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION, NULL);
//        curl_easy_setopt(curl, CURLOPT_ENCODING, "gzip, deflate");

        struct curl_slist *curl_headers = NULL;

        for (auto &key_value :headers) {
            auto header = std::ostringstream();
            header << key_value.first << ": " << key_value.second;

            curl_headers = curl_slist_append(curl_headers, header.str().c_str());
        }

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);

        auto response = std::string();

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


        CURLcode perform_result = curl_easy_perform(curl);

        curl_slist_free_all(curl_headers);

        if (perform_result != CURLE_OK) {
            throw Exception("Failure perform request");
        }

        return response;
    }

    std::map<std::string, std::string> getHeaders() const
    {
        return headers;
    }

    void setHeaders(const std::map<std::string, std::string> &value)
    {
        headers = value;
    }

    void addHeader(std::string name, std::string value) {
        headers[name] = value;
    }

    virtual ~HTTPRequestImpl() {
        curl_easy_cleanup(curl);
    }
};

HTTPRequest::HTTPRequest(std::string URL): impl(new HTTPRequestImpl(URL))
{
}

std::string HTTPRequest::getURL() const
{
    return impl->getURL();
}

void HTTPRequest::setURL(const std::string &value)
{
    impl->setURL(value);
}

std::string HTTPRequest::getBody() const
{
    return impl->getBody();
}

void HTTPRequest::setBody(const std::string &value)
{
    impl->setBody(value);
}

std::string HTTPRequest::perform()
{
    return impl->perform();
}

void HTTPRequest::setHeaders(const std::map<std::string, std::string> &value)
{
    impl->setHeaders(value);
}

std::map<std::string, std::string> HTTPRequest::getHeaders() const
{
    return impl->getHeaders();
}

HTTPRequest& HTTPRequest::addHeader(std::string name, std::string value) {
    impl->addHeader(name, value);

    return *this;
}

HTTPRequest::~HTTPRequest() {

}

}
