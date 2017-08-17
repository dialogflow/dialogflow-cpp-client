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

#include <apiai/query/request/RequestContext.h>
#include <apiai/exceptions/InvalidArgumentException.h>

using namespace std;
using namespace ai::query::request;

RequestContext::RequestContext(
        std::string name,
        int lifespan,
        std::map<std::string, std::string> parameters):
    name(name), lifespan(lifespan), parameters(parameters)
{

}

const int& RequestContext::getLifespan() const
{
    return this->lifespan;
}

void RequestContext::setLifespan(const int& lifespan)
{
    this->lifespan = lifespan;
}

RequestContext& RequestContext::addParameter(std::string name, std::string value)
{
    if (name.size() == 0) {
        throw InvalidArgumentException("Name cannot be empty.");
    }

    if (value.size() == 0) {
        throw InvalidArgumentException("Value cannot be empty.");
    }

    parameters[name] = value;

    return *this;
}

const std::string& RequestContext::getName() const
{
    return name;
}

void RequestContext::setName(const std::string& name)
{
    if (name.size() == 0) {
        throw InvalidArgumentException("Name cannot be empty.");
    }
    this->name = name;
}

const std::map<std::string, std::string>& RequestContext::getParameters() const
{
    return parameters;
}

void RequestContext::setParameters(const std::map<std::string, std::string>& parameters)
{
    this->parameters.clear();

    for (auto& parameter: parameters) {
        this->addParameter(parameter.first, parameter.second);
    }
}
