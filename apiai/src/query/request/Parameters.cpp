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

#include <apiai/query/request/Parameters.h>
#include <apiai/exceptions/InvalidArgumentException.h>

using namespace std;
using namespace ai::query::request;

Parameters::Parameters(std::string sessionId,
                       bool resetContexts,
                       std::shared_ptr<std::string> timeZone,
                       std::vector<RequestContext> contexts,
                       std::vector<Entity> entities
                       ):
    sessionId(sessionId), resetContexts(resetContexts), timeZone(timeZone), contexts(contexts), entities(entities)
{
    if (sessionId.size() == 0) {
        throw InvalidArgumentException("SessionId connot be zero length.");
    }
}

Parameters& Parameters::setResetContexts(bool resetContexts)
{
    this->resetContexts = resetContexts;
    return *this;
}

Parameters& Parameters::setTimeZone(std::shared_ptr<std::string> timeZone)
{
    this->timeZone = timeZone;
    return *this;
}

Parameters& Parameters::addContext(RequestContext context)
{
    this->contexts.push_back(context);
    return *this;
}

Parameters& Parameters::addEntity(Entity entity)
{
    this->entities.push_back(entity);
    return *this;
}

bool Parameters::getResetContexts() const
{
    return resetContexts;
}

std::string Parameters::getSessionId() const
{
    return sessionId;
}

std::shared_ptr<std::string> Parameters::getTimeZone() const
{
    return timeZone;
}

std::vector<RequestContext> Parameters::getContexts() const
{
    return contexts;
}

std::vector<Entity> Parameters::getEntities() const
{
    return entities;
}

