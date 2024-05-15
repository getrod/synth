//
// Created by Kevin on 2/29/2020.
//

#ifndef ANDROID_AUDIOENGINE_H
#define ANDROID_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include "buukSynth/Synth.h"
using namespace oboe;

class AudioEngine : public AudioStreamCallback{
public:
    AudioEngine();
    ~AudioEngine();

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;
    Synth* synth;
private:
    void start();
};

#endif //ANDROID_AUDIOENGINE_H
