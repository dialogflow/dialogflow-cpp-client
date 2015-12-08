#ifndef VOICEREQUEST_H
#define VOICEREQUEST_H

#include <functional>
#include <string>
#include <memory>

#include "QueryRequest.h"

namespace ai {
    namespace query {
        namespace request {

            ///
            /// \brief  The VoiceRecorder class defines a programmatic interface
            ///         for voice recording.
            ///

            class VoiceRecorder {
            public:

                virtual ~VoiceRecorder() {
                }

                virtual VoiceRecorder &write(const char *source, std::streamsize count) = 0;

                virtual void flush() = 0;
            };

            ///
            /// \brief  The VoiceSource defines a programmatic interface for
            ///         interaction with the voice recorders.
            ///
            /// \param  recorder    An object responsible for voice recording.
            ///                     Note that the voice sources are obliged to
            ///                     manage recorder's lifecycle; that means
            ///                     the voice sources are responsible for
            ///                     deletion of the recorder.
            ///

            typedef std::function<void(VoiceRecorder *recorder)> VoiceSource;

            ///
            /// \brief  The VoiceRequest class defines a programmatic interface
            ///         for uploading natural language text as a sound file to
            ///         the server.
            ///

            class VoiceRequest : public QueryRequest {
            public:

                VoiceRequest(const std::string &language,
                             const Credentials &credentials,
                             const Parameters &parameters);

                inline bool hasVoiceSource() const {
                    return static_cast<bool>(this->voiceSource_);
                }

                inline void setVoiceSource(const VoiceSource &voiceSource) {
                    this->voiceSource_ = voiceSource;
                }

                virtual response::Response perform() override;

            private:

                VoiceRequest(const VoiceRequest &disallowed);
                void operator=(const VoiceRequest &disallowed);

                std::string boundary_;
                VoiceSource voiceSource_;
            };
        }
    }
}

#endif // VOICEREQUEST_H
