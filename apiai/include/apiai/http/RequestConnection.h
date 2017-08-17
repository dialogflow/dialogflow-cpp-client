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

#ifndef REQUESTCONNECTION
#define REQUESTCONNECTION

#include <memory>
#include <string>
#include <map>

#define NON_COPYABLE_NOR_MOVABLE(T) \
      T(T const &) = delete; \
      void operator=(T const &t) = delete; \
      T(T &&) = delete;

namespace ai {
    class Credentials;

    namespace io {
        class StreamWriter;
    }

    class RequestConnection {

    protected:
        RequestConnection(std::string URL);

        std::string performConnection();
        void authentificate(const Credentials& credentials);

        virtual ~RequestConnection();

        class RequestConnectionImpl;
        std::unique_ptr<RequestConnectionImpl> impl;
    private:
        NON_COPYABLE_NOR_MOVABLE(RequestConnection)
    };
}

#endif // REQUESTCONNECTION

