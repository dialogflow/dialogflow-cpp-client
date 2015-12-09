#ifndef VOICE_ACTIVITY_DETECTOR_h
#define VOICE_ACTIVITY_DETECTOR_h

#include <stdio.h>

#include "VADState.h"

struct VADContext;
typedef struct VADContext *VADContextRef;

namespace ai {
    namespace vad {

        class VoiceActivityDetector {
        public:

            VoiceActivityDetector();

            ~VoiceActivityDetector();

            VADState analyseFrames(const short *frames, size_t count);

            void reset();

        private:

            VADContextRef context_;
        };
    }
}

#endif // VOICE_ACTIVITY_DETECTOR_h
