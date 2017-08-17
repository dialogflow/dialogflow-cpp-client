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

#include "VADContext.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHUNK_SIZE 160

//  ZCR stands for Zero Crossing Rate
#define ZCR_MIN  5
#define ZCR_MAX 15

//  Defines minimal permissible energy value
#define NOISE_ENERGY_MIN    0.001818

struct VADContext {
    VADState state;
    short *buffer;
    size_t frames_count;

    float energy_factor;
    size_t first_frames_count;
    size_t noise_frames_count;

    float noise_energy;

    size_t frame_number;
    double last_active_time;
    double last_sequence_time;
    size_t sequence_counter;
    double time;

    double max_silence_length_milis;
    double min_silence_length_milis;
    double silence_length_milis;
    double sequence_length_milis;
    size_t min_sequence_count;

    double sample_rate;
};

void VADContextReleaseBuffer(VADContextRef context);

void VADContextPushFrames(const VADContextRef context, const short *frames, size_t frames_count);
short *VADContextPopFrames(const VADContextRef context, size_t frames_count);

VADState VADContextProcessFrames(const VADContextRef context, const short *frames, size_t frames_count);

float VADFrameCalculateEnergy(const float *frames, size_t frames_count);
float *VADFrameNormalize(const short *frames, size_t frames_count);
size_t VADFrameCalculateZeroCrossingRate(const short *frame, size_t frames_count);

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///                 Life-cycle
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VADContextRef VADContextCreate() {
    VADContextRef context = (VADContextRef)malloc(sizeof(struct VADContext));

    context->buffer = NULL;
    context->frames_count = 0;

    VADContextReset(context);

    return context;
}

void VADContextRelease(VADContextRef context) {
    if (context != NULL) {
        VADContextReleaseBuffer(context);
        free(context);

        context = NULL;
    }
}

void VADContextReleaseBuffer(VADContextRef context) {
    if (context->buffer) {
        free(context->buffer);
        context->buffer = NULL;
    }

    context->frames_count = 0;
}

void VADContextReset(const VADContextRef context) {
    context->state = VADStateUnknown;
    VADContextReleaseBuffer(context);

    context->frames_count = 0;
    context->energy_factor = 3.1f;
    context->first_frames_count = 0;
    context->noise_frames_count = 15;
    context->noise_energy = 0.f;

    context->frame_number = 0;
    context->last_active_time = -1.0;
    context->last_sequence_time = 0.0;
    context->sequence_counter = 0;
    context->time = 0.f;

    context->min_silence_length_milis = 0.8;
    context->silence_length_milis = context->max_silence_length_milis = 3.5;
    context->sequence_length_milis = 0.03;
    context->min_sequence_count = 3;

    context->sample_rate = 16000.0;

    context->state = VADStateUnknown;
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///                 Analysis
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VADState VADContextAnalyseFrames(const VADContextRef context, const short *frames, size_t frames_count)
{
    if (!context) {
        return VADStateError;
    }
    else if (!frames || (frames_count == 0)) {
        context->state = VADStateError;
    }
    else if ((context->state == VADStateEndOfSpeech) || (context->state == VADStateError)) {
        return context->state;
    }
    else {
        VADContextPushFrames(context, frames, frames_count);
        while ((context->frames_count >= CHUNK_SIZE) && (context->state != VADStateEndOfSpeech)) {
            short *const chunk = VADContextPopFrames(context, CHUNK_SIZE);
            if (chunk == NULL) {
                context->state = VADStateError;
                break;
            }

            context->state = VADContextProcessFrames(context, chunk, CHUNK_SIZE);
            free(chunk);
        }
    }

    return context->state;
}

void VADContextPushFrames(const VADContextRef context, const short *frames, size_t frames_count) {
    size_t const current_frames_count = context->frames_count;
    size_t const received_frames_count = frames_count;
    size_t const total_frames_count = current_frames_count + received_frames_count;

    short *res = (short *)malloc(sizeof(short) * total_frames_count);
    if (current_frames_count) {
        memcpy(res, context->buffer, current_frames_count * sizeof(short));
        memcpy(res + current_frames_count, frames, received_frames_count * sizeof(short));
        free(context->buffer);
    }
    else {
        memcpy(res, frames, received_frames_count * sizeof(short));
    }
    context->buffer = res;
    res = NULL;

    context->frames_count = total_frames_count;
}

short *VADContextPopFrames(const VADContextRef context, size_t frames_count) {
    if (context->frames_count < frames_count) {
        return NULL;
    }

    size_t const current_size = context->frames_count;
    size_t const result_size = current_size - frames_count;

    short *res = (short *)malloc(sizeof(short) * result_size);
    short *frames = (short *)malloc(sizeof(short) * frames_count);

    memcpy(res, context->buffer + frames_count, result_size * sizeof(short));
    memcpy(frames, context->buffer, frames_count * sizeof(short));

    free(context->buffer);
    context->buffer = res;
    res = NULL;

    context->frames_count = result_size;

    return frames;
}

VADState VADContextProcessFrames(const VADContextRef context, const short *frames, size_t frames_count) {
    // XXX: Wouldn't it be more efficient to calculate energy on demand?
    float *normalized_frames = VADFrameNormalize(frames, frames_count);
    float const energy = VADFrameCalculateEnergy(normalized_frames, frames_count);
    free(normalized_frames);

    bool is_frame_active = false;
    if (context->first_frames_count < context->noise_frames_count) {
        context->first_frames_count++;
        context->noise_energy += energy / (float)context->noise_frames_count;

        is_frame_active = false; // XXX: Isn't this redundant?
    }
    else {
        size_t const zcr = VADFrameCalculateZeroCrossingRate(frames, frames_count);
        if ((zcr >= ZCR_MIN) && (zcr <= ZCR_MAX)) {
            if (energy >= fmaxf(context->noise_energy, NOISE_ENERGY_MIN) * context->energy_factor) {
                is_frame_active = true;
            }
        }
    }

    context->time = ((++context->frame_number) * (double)CHUNK_SIZE) / context->sample_rate;

    if (is_frame_active) {
        if ((context->last_active_time >= 0) && (context->time - context->last_active_time) < context->sequence_length_milis) {
            context->sequence_counter++;
            if (context->sequence_counter >= context->min_sequence_count) {
                context->last_sequence_time = context->time;
                context->silence_length_milis = fmax(context->min_silence_length_milis, context->silence_length_milis - (context->max_silence_length_milis - context->min_silence_length_milis) / 4);
            }
        }
        else {
            context->sequence_counter = 1;
        }
        context->last_active_time = context->time;
    }
    else {
        if (context->time - context->last_sequence_time > context->silence_length_milis) {
            return (context->last_sequence_time > 0) ? VADStateEndOfSpeech : VADStateNoSpeech;
        }
    }

    return VADStateInProgress;
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///         Frame-specific functions
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

float VADFrameCalculateEnergy(const float *frames, size_t frames_count) {
    float energy = 0.f;
    size_t i = 0;

    for (i = 0; i < frames_count; i++) {
        energy += frames[i] * frames[i];
    }

    return energy / (float)frames_count;
}

float *VADFrameNormalize(const short *frames, size_t frames_count) {
    float *const normalized_frames = (float *)malloc(sizeof(float) * frames_count);
    size_t i = 0;
    for (i = 0; i < frames_count; i++) {
        normalized_frames[i] = frames[i] / (float)SHRT_MAX;
    }

    return normalized_frames;
}

size_t VADFrameCalculateZeroCrossingRate(const short *frame, size_t frames_count) {
    size_t zcr = 0;
    short sign = 0;
    short last_sign = 0;

    size_t i = 0;
    for (i = 0; i < frames_count; i++) {
        sign = (frame[i] > 0) ? 1 : -1;

        if ((last_sign != 0) && (sign != last_sign)) {
            zcr++;
        }
        last_sign = sign;
    }

    return zcr;
}

#undef CHUNK_SIZE

#undef ZCR_MIN
#undef ZCR_MAX

#undef NOISE_ENERGY_MIN
