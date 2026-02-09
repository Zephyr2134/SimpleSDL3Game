#include "ECS.hpp"
#include "Components.hpp"
#include <SDL3/SDL.h>
#include <iostream>

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
        spec.channels = 1;
        spec.format = SDL_AUDIO_F32;
        spec.freq = 8000;
        stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
        if (!stream) {
            SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
            return;
        }
        SDL_ResumeAudioStreamDevice(stream);
    }

    void update() override
    {
        minimum_audio = (8000 * sizeof (float)) / 2;
         if (SDL_GetAudioStreamQueued(stream) < minimum_audio) {
            float samples[512];

            for (int i = 0; i < SDL_arraysize(samples); i++) {
            const int freq = 440;
            const float phase = currentSineSample * freq / 8000.0f;
            samples[i] = SDL_sinf(phase * 2 * SDL_PI_F);
            currentSineSample++;
        }

        currentSineSample %= 8000;

        SDL_PutAudioStreamData(stream, samples, sizeof (samples));
    }
    }

    void draw() override {}

private:
    SDL_AudioStream* stream;
    SDL_AudioSpec spec;
    int currentSineSample;
    int minimum_audio;
};