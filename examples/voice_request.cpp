#include <iostream>
#include <fstream>
#include <string>

#include <apiai/AI.h>
#include <apiai/Credentials.h>

#include <apiai/query/VoiceRequest.h>
#include <apiai/query/request/Parameters.h>

#ifndef RECORD_VOICE_ASYNCHRONOUSLY
//    #define RECORD_VOICE_ASYNCHRONOUSLY 1
#endif

static void *recordVoice(ai::query::request::VoiceRecorder *const recorder) {
    std::string filePath(getcwd(NULL, 0));
    filePath.append("/../apiai/io/tests/sounds/sound2.wav");

    std::cout << "Voice source is located at " << filePath << std::endl;

    std::ifstream fstream = std::ifstream(filePath.c_str(), std::ifstream::binary);

    fstream.seekg(0, fstream.end);
    std::streamsize length = fstream.tellg();
    fstream.seekg(0, fstream.beg);

    const std::streamsize bufferSize = 2048;
    std::unique_ptr<char []> buffer(new char[bufferSize]);
    while (length > 0) {
        const std::streamsize read = (bufferSize > length) ? length : bufferSize;

        fstream.read(buffer.get(), read);
        recorder->write(buffer.get(), read);
        recorder->flush();

        length -= read;
    }
    buffer.reset(nullptr);

    return NULL;
}

static void *detached_main(void *arg) {
    using namespace ai::query::request;

    std::unique_ptr<VoiceRecorder> recorder(reinterpret_cast<VoiceRecorder *>(arg));
    if (recorder == nullptr) {
        return NULL;
    }

    return recordVoice(recorder.get());
}

int main(int argc, char *argv[]) {

    ai::AI::global_init();

    auto credentials = ai::Credentials("ff98c090685f484caaffada53cdce7b3", "4c91a8e5-275f-4bf0-8f94-befa78ef92cd");
    auto params = ai::query::request::Parameters("<session id unique for every user>")
            .addEntity(
                ai::query::request::Entity("dwarfs")
                    .addEntry(
                        ai::query::request::Entry("Ori").addSynonym("ori").addSynonym("Nori")
                    ).addEntry(
                        ai::query::request::Entry("bifur").addSynonym("Bofur").addSynonym("Bombur")
                    )
            ).addContext(
                ai::query::request::RequestContext("context")
            );

    auto request = std::unique_ptr<ai::query::request::VoiceRequest>(
        new ai::query::request::VoiceRequest(/*filePath,*/ "en", credentials, params)
    );

    request->setVoiceSource([](ai::query::request::VoiceRecorder *const recorder) {
    #ifdef RECORD_VOICE_ASYNCHRONOUSLY
        pthread_t thread;
        if (pthread_create(&thread, NULL, &detached_main, reinterpret_cast<void *>(recorder)) == 0) {
            pthread_detach(thread);
        }
        else {
            abort();
        }
    #else
          detached_main(reinterpret_cast<void *>(recorder));
    #endif
    });

    auto response = request->perform();

    std::cout << "Server's replied with: " << std::endl << response << std::endl;

    ai::AI::global_clean();

    return 0;
}

#undef RECORD_VOICE_ASYNCHRONOUSLY
