#include <iostream>

#include <apiai/query/VoiceRequest.h>

#include <portaudio.h>

static int MyPaStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData )
{
    std::cout << "Hello!" << std::endl;

    return paContinue;
}

int main(int argc, char *argv[]) {
    Pa_Initialize();

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

    PaStream* stream = NULL;

    auto open_error =
    Pa_OpenStream(&stream,
                  &stream_parameters,
                  NULL,
                  16000.0,
                  512,
                  paNoFlag,
                  MyPaStreamCallback,
                  NULL);

    auto start_error = Pa_StartStream(stream);

    PaError err = paNoError;

    while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
    {
        Pa_Sleep(1000);
    }

    Pa_Terminate();
    return 0;
}
