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

#ifndef VAD_CONTEXT_H
#define VAD_CONTEXT_H

#include <apiai/vad/VADState.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct VADContext *VADContextRef;

    VADContextRef VADContextCreate();
    void VADContextRelease(VADContextRef context);

    VADState VADContextAnalyseFrames(const VADContextRef context, const short *frames, size_t frames_count);
    void VADContextReset(const VADContextRef context);

#ifdef __cplusplus
}
#endif

#endif // VAD_CONTEXT_H
