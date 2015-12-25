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
