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
