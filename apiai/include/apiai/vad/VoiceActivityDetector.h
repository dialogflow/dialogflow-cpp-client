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
