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

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <future>
#include <sstream>

#include <apiai/Credentials.h>

#include "RequestSerialize.h"

namespace ai {
    template <typename T>
    class Request: protected RequestSerialize<T> {
    public:
        virtual T perform() {
            return RequestSerialize<T>::perform();
        }
    protected:
        Request(const Credentials &credentials): RequestSerialize<T>(std::string("https://api.api.ai/v1/query?v=20150910")), credentials(credentials)
        {
            this->authentificate(credentials);
        }
    private:
        Request(const Request&);
        Credentials credentials;
    };
}

#endif // REQUEST_H
