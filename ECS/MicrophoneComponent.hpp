#include "ECS.hpp"
#include "Components.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

class MicrophoneComponent : public Component
{
public:
    MicrophoneComponent() {}
    ~MicrophoneComponent()
    {
        if (stream)
        {
            SDL_DestroyAudioStream(stream);
        }
    }

    void init() override
    {
        mic =
        SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, NULL);

        SDL_GetAudioDeviceFormat(mic, &src, NULL);

        dst.freq = 48000;
        dst.channels = 1;
        dst.format = SDL_AUDIO_F32;

    stream = SDL_CreateAudioStream(&src, &dst);
    SDL_BindAudioStream(mic, stream);
    SDL_ResumeAudioDevice(mic);
    }

    void update() override
    {
        float samples[1024];

        int bytes = SDL_GetAudioStreamData(stream, samples, sizeof(samples));
        if (bytes <= 0)
            return;

        int frames = bytes / sizeof(float);
        if (frames == 0)
            return;

        /*float rms = 0.0f;
        for (int i = 0; i < frames; i++)
            rms += samples[i] * samples[i];

        rms = sqrt(rms / frames);
        std::cout << rms << std::endl;*/
        int crossings = 0;
        for (int i = 1; i < frames; i++) {
            if (samples[i-1] < 0 && samples[i] >= 0)
                crossings++;
        }
        float frequency = (crossings * 48000) / (2.0f * frames);
        std::cout << frequency << std::endl;

    }

    void draw() override {}

private:
    SDL_AudioDeviceID mic;
    SDL_AudioStream* stream;
    SDL_AudioSpec src;
    SDL_AudioSpec dst;
};