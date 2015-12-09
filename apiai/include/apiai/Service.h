#ifndef SERVICE_H
#define SERVICE_H

#include "Credentials.h"
#include "query/request/Parameters.h"

namespace ai {

    namespace query {
        namespace request {
            class TextQueryRequest;
            class VoiceRequest;
            class QueryText;
        }
    }

    class Service
    {
    private:
        Credentials credentials;
        query::request::Parameters parameters;
        std::string language;

    public:
        Service(Credentials credentials, query::request::Parameters parameters, std::string language = "en");

        std::shared_ptr<query::request::TextQueryRequest> textQueryRequest(const std::shared_ptr<query::request::QueryText> &query);
        std::shared_ptr<query::request::VoiceRequest> voiceQueryRequest();

        const Credentials& getCredentials() const;
        void setCredentials(const Credentials &value);

        const query::request::Parameters& getParameters() const;
        void setParameters(const query::request::Parameters &value);

        const std::string& getLanguage() const;
        void setLanguage(const std::string &value);

        virtual ~Service();
    };
}

#endif // SERVICE_H
