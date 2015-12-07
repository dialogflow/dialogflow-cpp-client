#ifndef VOICEFILEREQUEST_H
#define VOICEFILEREQUEST_H

#include "QueryRequest.h"

#include <fstream>
#include <memory>
#include <string>

namespace ai {
    class Credentials;

    namespace query {
        namespace request {

            class VoiceFileRequest : public QueryRequest {
            public:

                VoiceFileRequest(const std::string &filePath,
                                 const std::string &language,
                                 const Credentials &credentials,
                                 const Parameters &parameters);

                virtual response::Response perform() override;

            private:

                VoiceFileRequest(const VoiceFileRequest &disallowed);
                void operator=(const VoiceFileRequest & disallowed);

                std::string boundary_;
                std::string filePath_;
            };
        }
    }
}

#endif // VOICEFILEREQUEST_H
