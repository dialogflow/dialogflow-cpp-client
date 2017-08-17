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
