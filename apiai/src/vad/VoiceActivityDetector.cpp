#include <apiai/vad/VoiceActivityDetector.h>

#include "VADContext.h"

namespace ai {
    namespace vad {

        VoiceActivityDetector::VoiceActivityDetector() :
            context_(VADContextCreate()) {
        }

        VoiceActivityDetector::~VoiceActivityDetector() {
            VADContextRelease(this->context_);
        }

        VADState VoiceActivityDetector::analyseFrames(const short *frames, size_t count) {
            return VADContextAnalyseFrames(this->context_, frames, count);
        }

        void VoiceActivityDetector::reset() {
            VADContextReset(this->context_);
        }
    }
}
