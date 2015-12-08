#ifndef REQUESTCONNECTIONIMPL_H
#define REQUESTCONNECTIONIMPL_H

#include <apiai/http/RequestConnection.h>

#include <map>

#include <curl/curl.h>
#include "../io/Stream.h"
#include "../io/StreamWriter.h"
#include "../io/StreamReader.h"

namespace ai {
    class RequestConnection::RequestConnectionImpl
    {
    public:
        RequestConnectionImpl(const std::string &URL);

        std::string getBody();
        void setBody(const std::string &value);

        io::StreamWriter getBodyStreamWriter();

        const std::string &getURL() const;
        void setURL(const std::string &value);

        const std::map<std::string, std::string> &getHeaders() const;
        void setHeaders(const std::map<std::string, std::string> &value);

        RequestConnectionImpl& addHeader(const std::string &name, const std::string &value);

        std::string performConnection();

        virtual ~RequestConnectionImpl();
    private:
        static size_t read_callback(char *ptr, size_t size, size_t nmemb, io::StreamReader *reader);

        static uint write_callback(char *in, uint size, uint nmemb, std::string *response);

        CURL *curl;
        std::string URL;

        io::Stream bodyStream;

        std::map<std::string, std::string> headers;
    };
}

#endif // REQUESTCONNECTIONIMPL_H
