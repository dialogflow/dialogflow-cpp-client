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

#include <apiai/Service.h>

#include <apiai/query/TextQueryRequest.h>
#include <apiai/query/VoiceRequest.h>

using namespace std;

using namespace ai;
using namespace ai::query::request;

Service::Service(Credentials credentials, Parameters parameters, std::string language):
    credentials(credentials), parameters(parameters), language(language)
{

}

std::shared_ptr<TextQueryRequest> Service::textQueryRequest(const std::shared_ptr<QueryText> &query)
{
    return shared_ptr<TextQueryRequest>(new TextQueryRequest(query, language, credentials, parameters));
}

std::shared_ptr<VoiceRequest> Service::voiceQueryRequest()
{
    return shared_ptr<VoiceRequest>(new VoiceRequest(language, credentials, parameters));
}

const Credentials& Service::getCredentials() const
{
    return credentials;
}

void Service::setCredentials(const Credentials &value)
{
    credentials = value;
}

const query::request::Parameters& Service::getParameters() const
{
    return parameters;
}

void Service::setParameters(const query::request::Parameters &value)
{
    parameters = value;
}

const std::string& Service::getLanguage() const
{
    return language;
}

void Service::setLanguage(const std::string &value)
{
    language = value;
}

Service::~Service()
{

}
