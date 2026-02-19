#pragma once
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

    mic = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_RECORDING, NULL);
    if (!mic) {
        SDL_Log("OpenAudioDevice failed: %s", SDL_GetError());
        return;
    }

    if (!SDL_GetAudioDeviceFormat(mic, &src, NULL)) {
        SDL_Log("GetAudioDeviceFormat failed: %s", SDL_GetError());
        return;
    }

    dst.freq = 48000;
    dst.channels = 1;
    dst.format = SDL_AUDIO_F32;

    stream = SDL_CreateAudioStream(&src, &dst);
    if (!stream) {
        SDL_Log("CreateAudioStream failed: %s", SDL_GetError());
        return;
    }

    if (!SDL_BindAudioStream(mic, stream)) {
        SDL_Log("BindAudioStream failed: %s", SDL_GetError());
        return;
    }

    SDL_ResumeAudioDevice(mic);
    }

    float detectFrequency(float* samples, int frames, float sample_rate)
{
    int minLag = sample_rate / 1000;
    int maxLag = sample_rate / 50;

    float bestCorrelation = 0.0f;
    int bestLag = 0;

    for (int lag = minLag; lag < maxLag; lag++)
    {
        float correlation = 0.0f;

        for (int i = 0; i < frames - lag; i++)
            correlation += samples[i] * samples[i + lag];

        if (correlation > bestCorrelation)
        {
            bestCorrelation = correlation;
            bestLag = lag;
        }
    }

    if (bestLag == 0)
        return 0.0f;

    return sample_rate / bestLag;
}

    void update() override
    {
        float samples[1024]; 
        int bytes = SDL_GetAudioStreamData(stream, samples, sizeof(samples)); 
        if (bytes <= 0) return; 
        int frames = bytes / sizeof(float); 
        if (frames == 0) return; 

        float freq = detectFrequency(samples, frames, dst.freq);

        if (freq > 0.0f){
            if (fabs(freq - currentFreq) > 1.0f)  // 1 Hz threshold
    {
        std::cout << "Frequency: " << freq << " Hz\n";
        currentFreq = freq;
    }
            }
    }

    void draw() override {}

     float currentFreq = 0.0f;

private:
    SDL_AudioDeviceID mic;
    SDL_AudioStream* stream;
    SDL_AudioSpec src;
    SDL_AudioSpec dst;
   
};