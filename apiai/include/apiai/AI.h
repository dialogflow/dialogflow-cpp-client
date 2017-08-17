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

#ifndef AI_H
#define AI_H

#include "Credentials.h"
#include "Service.h"
#include "common/Deprecated.h"

#include <mutex>

namespace ai {
    class Credentials;
    namespace query {
        namespace request {
            class Parameters;
        }
    }

    class AI
    {
    private:
        static std::shared_ptr<Credentials> credentials;
        static std::shared_ptr<query::request::Parameters> parameters;
    public:
        static void global_init();
        static void global_clean();

        static void setupDefaultParameters(const query::request::Parameters& parameters);

        static void configure(const Credentials &credentials);
        DEPRECATED static void configure(const std::string &clientAccessToken, const std::string &subscribtionKey);

        static void configure(const std::string &clientAccessToken);

        static Service& sharedService();
    };
}

#endif // AI_H
