#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "VoiceFileRequest.h"

#include "cJSON.h"

#include "response/Response.h"
#include "../io/StreamWriter.h"

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

    class Upload {
    public:

        static void *readFile(void *arg) {
            Upload *const upload =
                    reinterpret_cast<Upload *>(arg);
            if (upload == nullptr) {
                return NULL;
            }

            std::ifstream &fstream = upload->input();
            ai::io::StreamWriter &writer = upload->output();

            fstream.seekg(0, fstream.end);
            std::streamsize length = fstream.tellg();
            fstream.seekg(0, fstream.beg);

            const std::streamsize sizeOfBuffer = 2048;
            std::unique_ptr<char []> buffer(new char[sizeOfBuffer]);
            while (length > 0) {
                const std::streamsize read =
                        (sizeOfBuffer > length) ? length : sizeOfBuffer;

                fstream.read(buffer.get(), read);
                writer.write(buffer.get(), read);
                writer.flush();

                length -= sizeOfBuffer;
            }
            buffer.reset(nullptr);

            writer.write(details::string_format("\r\n--%s--\r\n", upload->boundary().c_str()));
            writer.flush();
            writer.sealed(true);

            return NULL;
        }

        Upload(const std::string &filePath, ai::io::StreamWriter &output, const std::string &boundary):
            input_(std::ifstream(filePath.c_str(), std::ifstream::binary)),
            output_(output),
            boundary_(boundary) {
        }

        inline const std::string &boundary() const {
            return this->boundary_;
        }

        inline std::ifstream &input() {
            return this->input_;
        }

        inline ai::io::StreamWriter &output() {
            return this->output_;
        }

    private:

        std::string boundary_;

        std::ifstream input_;
        ai::io::StreamWriter output_;
    };
}

VoiceFileRequest::VoiceFileRequest(
        const std::string &filePath,
        const std::string &language,
        const Credentials &credentials,
        const Parameters &parameters):

    QueryRequest(language, credentials, parameters),
    boundary_(details::createBoundary()),
    filePath_(filePath) {
    const std::string contentType = details::string_format(
        "multipart/form-data; boundary=%s", this->boundary_.c_str()
    );
    httpRequest
            .addHeader("Accept", "application/json; charset=utf-8")
            .addHeader("Content-Type", contentType)
            .addHeader("Transfer-Encoding", "chunked");
}

Response VoiceFileRequest::perform() {
    ai::io::StreamWriter writer = httpRequest.getBodyStreamWriter();
    details::Upload upload(this->filePath_, writer, this->boundary_);

    writer.write(details::string_format("--%s\r\n", upload.boundary().c_str()));
    writer.write("Content-Disposition: form-data; name=\"request\"; filename=\"request.json\"\r\n");
    writer.write("Content-Type: application/json; charset=utf-8\r\n\r\n");

    {
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
    }

    writer.write(details::string_format("\r\n--%s\r\n", upload.boundary().c_str()));
    writer.write("Content-Disposition: form-data; name=\"voiceData\"; filename=\"recording.mp4\"\r\n");
    writer.write(details::string_format("Content-Type: %s\r\n\r\n", "audio/wav"));
    writer.flush();

    pthread_t thread;
    if (pthread_create(&thread, NULL, &details::Upload::readFile, (void *)&upload) == 0) {
        pthread_detach(thread);
    }
    else {
        // TODO: Provide a proper error handler.
        abort();
    }

    return QueryRequest::perform();
}
