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

#ifndef REQUESTSERIALIZE
#define REQUESTSERIALIZE

#include "RequestConnection.h"

#include <apiai/exceptions/InvalidArgumentException.h>
#include <apiai/exceptions/JSONException.h>

#include <iostream>

namespace ai{
    template <typename T>
    class RequestSerialize: public RequestConnection {
    public:
        virtual T perform() {
            try {
                auto resp = this->performConnection();
                return this->serialize(resp);
            } catch(...) {
                throw;
            }
        }
    protected:
        RequestSerialize(std::string URL): RequestConnection(URL) {}
        virtual T serialize(const std::string& response) = 0;
    };
}

#endif // REQUESTSERIALIZE

