#include <iostream>
#include <string>

#include "AI.h"
#include "Credentials.h"
#include "io/StreamWriter.h"
#include "query/VoiceFileRequest.h"
#include "query/request/Parameters.h"

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

    std::string filePath(getcwd(NULL, 0));
    filePath.append("/../apiai/io/tests/sounds/sound2.wav");

    std::cout << "File to upload: " << filePath << std::endl;

    auto request = std::unique_ptr<ai::query::request::VoiceFileRequest>(
        new ai::query::request::VoiceFileRequest(filePath, "en", credentials, params)
    );
    auto response = request->perform();

    std::cout << "Server's replied with: " << std::endl << response << std::endl;

    ai::AI::global_clean();

    return 0;
}
