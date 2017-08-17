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
