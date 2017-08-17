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

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include <apiai/query/VoiceRequest.h>

#include "cJSON.h"

#include <apiai/query/response/Response.h>
#include "../io/StreamWriter.h"

#include "../http/RequestConnectionImpl.h"

#include <string.h>

using namespace std;
using namespace ai::query::request;
using namespace ai::query::response;

namespace details {

    /// The string_format is taken from http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    /// TODO: It would be nice to move it out of this cpp file and make it public.
    template<typename ... Args>
    std::string string_format(const std::string &format, Args ... args) {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);

        return string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }

    static std::string createBoundary() {
        std::srand(std::time(NULL));
        return string_format("Boundary+%08X%08X", std::rand(), std::rand());
    }
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///             VoiceRecorderImpl
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class VoiceRecorderImpl: public VoiceRecorder {
public:

    VoiceRecorderImpl(const std::string &boundary, const ai::io::StreamWriter &target);

    virtual ~VoiceRecorderImpl();

    virtual VoiceRecorder &write(const char *source, std::streamsize count) override;

    virtual void flush() override;

private:

    std::string boundary_;
    ai::io::StreamWriter target_;
};

VoiceRecorderImpl::VoiceRecorderImpl(const string &boundary, const ai::io::StreamWriter &target) :
    boundary_(boundary), target_(target) {
}

VoiceRecorderImpl::~VoiceRecorderImpl() {
    this->target_.write(details::string_format("\r\n--%s--\r\n", this->boundary_.c_str()));
    this->target_.flush();
    this->target_.sealed(true);
}

VoiceRecorder &VoiceRecorderImpl::write(const char *source, streamsize count) {
    this->target_.write(source, count);

    return *this;
}

void VoiceRecorderImpl::flush() {
    this->target_.flush();
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///             VoiceRequest
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VoiceRequest::VoiceRequest(const std::string &language,
                           const Credentials &credentials,
                           const Parameters &parameters) :
    QueryRequest(language, credentials, parameters),
    boundary_(details::createBoundary()) {
    const std::string contentType = details::string_format(
        "multipart/form-data; boundary=%s", this->boundary_.c_str()
    );
    impl->
             addHeader("Accept", "application/json; charset=utf-8")
            .addHeader("Content-Type", contentType)
            .addHeader("Transfer-Encoding", "chunked");
}

Response VoiceRequest::perform() {
    ai::io::StreamWriter writer = impl->getBodyStreamWriter();

    writer.write(details::string_format("--%s\r\n", this->boundary_.c_str()));

    writer.write("Content-Disposition: form-data; name=\"request\"; filename=\"request.json\"\r\n");
    writer.write("Content-Type: application/json; charset=utf-8\r\n\r\n");

    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "lang", cJSON_CreateString(this->getLanguage().c_str()));

    const std::shared_ptr<std::string> timeZone = this->getParameters().getTimeZone();
    if (timeZone.get() != nullptr) {
        cJSON_AddItemToObject(root, "timezone", cJSON_CreateString(timeZone->c_str()));
    }

    cJSON_AddItemToObject(root, "sessionId", cJSON_CreateString(this->getParameters().getSessionId().c_str()));

    auto json = cJSON_Print(root);
    writer.write(json, strlen(json));
    free(json);

    cJSON_Delete(root);
    root = nullptr;

    if (this->hasVoiceSource()) {
        writer.write(details::string_format("\r\n--%s\r\n", this->boundary_.c_str()));

        writer.write("Content-Disposition: form-data; name=\"voiceData\"; filename=\"recording.mp4\"\r\n");
        writer.write(details::string_format("Content-Type: %s\r\n\r\n", "audio/wav"));

        writer.flush();

        this->voiceSource_(
            new VoiceRecorderImpl(this->boundary_, impl->getBodyStreamWriter())
        );
    }
    else {
        writer.write(details::string_format("\r\n--%s--\r\n", this->boundary_.c_str()));
        writer.flush();
        writer.sealed(true);
    }

    return QueryRequest::perform();
}
