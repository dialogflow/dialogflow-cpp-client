#include <iostream>
#include <fstream>
#include <string>

#include <apiai/vad/VADState.h>
#include <apiai/vad/VoiceActivityDetector.h>

#include <unistd.h>

#include <memory>



VADState analyseAudioFile() {
    char *cwd = getcwd(NULL, 0);
    std::string filePath(cwd);
    free(cwd);
    cwd = NULL;

    filePath.append("/../tests/vad/sounds/count-hammer.raw");

    std::cout << "Analysing: " << filePath << std::endl;

    std::ifstream fstream(filePath.c_str(), std::ifstream::binary);

    fstream.seekg(0, fstream.end);
    std::streamsize length = fstream.tellg();
    fstream.seekg(0, fstream.beg);

    VADState state = VADStateUnknown;
    ai::vad::VoiceActivityDetector detector;

    const size_t bufferSize = 160;

    std::shared_ptr<short> buffer(new short[bufferSize]);
    while (length > 0) {
        const size_t read = (bufferSize > length) ? length : bufferSize;

        fstream.read((char *)buffer.get(), read * sizeof(short));
        state = detector.analyseFrames((const short *)buffer.get(), read);
        if ((state != VADStateUnknown) && (state != VADStateInProgress)) {
            break;
        }

        length -= read;
    }

    std::cout << "Analysis has been finished with result: " << state << std::endl;

    return state;
}

int main(int argc, char *argv[]) {
    analyseAudioFile();

    return 0;
}
