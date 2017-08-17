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

#include <apiai/Credentials.h>

namespace ai {

PUSH_DEPRECATED_WARNING()

    const std::string &Credentials::getClientAccessToken() const
    {
        return clientAccessToken;
    }

    const std::string &Credentials::getSubscribtionKey() const
    {
        return subscribtionKey;
    }

    Credentials::Credentials(const std::string &clientAccessToken, const std::string &subscribtionKey):
        clientAccessToken(clientAccessToken)
    {
        this->subscribtionKey = subscribtionKey;
    }

    Credentials::Credentials(const std::string &clientAccessToken):
        clientAccessToken(clientAccessToken)
    {
        this->subscribtionKey = "";
    }

    Credentials::Credentials(const Credentials &credentials) {
        this->clientAccessToken = credentials.clientAccessToken;
        this->subscribtionKey = credentials.subscribtionKey;
    }

    Credentials::~Credentials() {

    }

POP_DEPRECATED_WARNING()
}
