#include <iostream>

#include <apiai/AI.h>
#include <apiai/query/VoiceRequest.h>

#include <portaudio.h>

using namespace ai::query::request;
using namespace ai::query::response;

typedef struct _RecordInfo {
    PaTime start_record_time;
    VoiceRecorder *recorder;
} RecordInfo;

static int MyPaStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData )
{
    RecordInfo* info = (RecordInfo *)userData;
    if (info->start_record_time < 0.0) {
        info->start_record_time = timeInfo->currentTime;
    }

    info->recorder->write((const char *)input, frameCount *sizeof(short));

    if (timeInfo->currentTime - info->start_record_time > 3) {
        return paComplete;
    }

    return paContinue;
}

int main(int argc, char *argv[]) {
    Pa_Initialize();
    ai::AI::global_init();

    auto default_input_device = Pa_GetDefaultInputDevice();
    auto device_info = Pa_GetDeviceInfo(default_input_device);

    PaStreamParameters stream_parameters = {
        .device = default_input_device,
        .channelCount = 1,
        .sampleFormat = paInt16,
        .suggestedLatency = 0.0,
        .hostApiSpecificStreamInfo = NULL
    };

    auto error = Pa_IsFormatSupported(&stream_parameters, NULL, 16000.0);

    if (error != paNoError) {
        return -1;
    }

    auto credentials = ai::Credentials("ff98c090685f484caaffada53cdce7b3", "4c91a8e5-275f-4bf0-8f94-befa78ef92cd");

    auto params = Parameters("<session id unique for every user>");

    VoiceRequest request("en", credentials, params);

    request.setVoiceSource([stream_parameters](ai::query::request::VoiceRecorder *recorder){
        PaStream* stream = NULL;

        RecordInfo info = {0};

        info.start_record_time = -1;
        info.recorder = recorder;

        auto open_error =
        Pa_OpenStream(&stream,
                      &stream_parameters,
                      NULL,
                      16000.0,
                      512,
                      paNoFlag,
                      MyPaStreamCallback,
                      &info);

        auto start_error = Pa_StartStream(stream);

        PaError err = paNoError;

        while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
        {
            Pa_Sleep(1000);
        }

        delete recorder;
    });

    auto response = request.perform();

    std::cout << response << std::endl;

    ai::AI::global_clean();
    Pa_Terminate();
    return 0;
}
