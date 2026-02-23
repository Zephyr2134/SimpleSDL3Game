#pragma once
#include "ECS.hpp"
#include "Components.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>

enum frequency
{
    C = 26163,
    CS = 27718,
    D = 29366,
    DS = 31113,
    E = 32963,
    F = 34923,
    FS = 36999,
    G = 39200,
    GS = 41530,
    A = 44000,
    AS = 46616,
    B = 49388,
};

struct Note
{
    public:

        Note(int o, frequency f)
        {
            octave = o;
            hertz = f;
        }
        int octave;
        frequency hertz;

};


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
    int minLag = sample_rate / 1000;   // 1000 Hz upper bound
    int maxLag = sample_rate / 50;     // 50 Hz lower bound

    std::vector<float> diff(maxLag, 0.0f);

    for (int tau = minLag; tau < maxLag; tau++)
    {
        float sum = 0.0f;

        for (int i = 0; i < frames - tau; i++)
        {
            float delta = samples[i] - samples[i + tau];
            sum += delta * delta;
        }

        diff[tau] = sum;
    }

    std::vector<float> cmnd(maxLag, 0.0f);

    cmnd[minLag] = 1.0f;

    float runningSum = 0.0f;

    for (int tau = minLag + 1; tau < maxLag; tau++)
    {
        runningSum += diff[tau];

        if (runningSum == 0.0f)
            cmnd[tau] = 1.0f;
        else
            cmnd[tau] = diff[tau] * tau / runningSum;
    }

    float threshold = 0.1f;

    int tauEstimate = -1;

    for (int tau = minLag; tau < maxLag; tau++)
    {
        if (cmnd[tau] < threshold)
        {
            while (tau + 1 < maxLag && cmnd[tau + 1] < cmnd[tau])
                tau++;

            tauEstimate = tau;
            break;
        }
    }

    if (tauEstimate == -1)
        return 0.0f;

        // 4️⃣ Parabolic interpolation
    float betterTau = tauEstimate;

    if (tauEstimate > 1 && tauEstimate < maxLag - 1)
    {
        float s0 = cmnd[tauEstimate - 1];
        float s1 = cmnd[tauEstimate];
        float s2 = cmnd[tauEstimate + 1];

        float denominator = (2 * s1 - s2 - s0);

        if (denominator != 0.0f)
        {
            betterTau += (s2 - s0) / (2 * denominator);
        }
    }

    return sample_rate / betterTau;
}


    void update() override
    {
        float samples[4096]; 
        
     int bytes = SDL_GetAudioStreamData(stream, samples, sizeof(samples)); 
        if (bytes <= 0) return; 
        int frames = bytes / sizeof(float); 
        if (frames == 0) return; 

        float rms = 0.0f;
        for (int i = 0; i < frames; i++)
            rms += samples[i] * samples[i];

        rms = sqrt(rms / frames);

        if (rms < 0.01f)
        {
            currentFreq = 0.0f;
            durationInFrames = 0;
            return;
        }

        float freq = detectFrequency(samples, frames, dst.freq);

if (freq > 0.0f)
{
    if (fabs(freq - stableFreq) < 5.0f)
    {
        stableCounter++;
    }
    else
    {
        stableCounter = 0;
        stableFreq = freq;
    }

    if (stableCounter > 6)
    {
        if(stableFreq != currentFreq)
        {
        durationInFrames = 0;
        currentFreq = stableFreq;
        std::cout << "Stable Frequency: " << currentFreq << ", helt for: " << durationInFrames << " , should be: " << (Notes[countInOrder].hertz/100.0f)*Notes[countInOrder].octave << std::endl;
        }
        else{
            durationInFrames++;
        }
    }
}

    if(countInOrder >= sizeof(Notes))
    {
      std::cout << "Correct" << std::endl;
    }
    else
    {
        Note targetNote = Notes[countInOrder];
        int octaveDistance = targetNote.octave - 4;
        if(octaveDistance > 0)
        {}
        else if(octaveDistance < 0)
        {}
        std::cout << countInOrder << std::endl;
        countInOrder++;
    }

    }

    void draw() override {}

     float currentFreq = 0.0f;
     int durationInFrames = 0;

private:
    SDL_AudioDeviceID mic;
    SDL_AudioStream* stream;
    SDL_AudioSpec src;
    SDL_AudioSpec dst;
   
    float stableFreq = 0.0f;
    int stableCounter = 0;

    int countInOrder = 0;
    Note Notes[4] = {{3, G}, {4, A}, {4, D}, {5, E}};
};