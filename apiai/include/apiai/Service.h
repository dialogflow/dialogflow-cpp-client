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

#ifndef SERVICE_H
#define SERVICE_H

#include "Credentials.h"
#include "query/request/Parameters.h"

namespace ai {

    namespace query {
        namespace request {
            class TextQueryRequest;
            class VoiceRequest;
            class QueryText;
        }
    }

    class Service
    {
    private:
        Credentials credentials;
        query::request::Parameters parameters;
        std::string language;

    public:
        Service(Credentials credentials, query::request::Parameters parameters, std::string language = "en");

        std::shared_ptr<query::request::TextQueryRequest> textQueryRequest(const std::shared_ptr<query::request::QueryText> &query);
        std::shared_ptr<query::request::VoiceRequest> voiceQueryRequest();

        const Credentials& getCredentials() const;
        void setCredentials(const Credentials &value);

        const query::request::Parameters& getParameters() const;
        void setParameters(const query::request::Parameters &value);

        const std::string& getLanguage() const;
        void setLanguage(const std::string &value);

        virtual ~Service();
    };
}

#endif // SERVICE_H
