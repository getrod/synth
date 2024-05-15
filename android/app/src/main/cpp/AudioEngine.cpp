//
// Created by Kevin on 11/8/2019.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine() {
    start();
}

AudioEngine::~AudioEngine() {
    //Delete Synth
}

void AudioEngine::start() {
    AudioStreamBuilder builder;

    builder.setCallback(this);
    builder.setPerformanceMode(PerformanceMode::LowLatency);
    builder.setSharingMode(SharingMode::Exclusive);
    builder.setChannelCount(ChannelCount::Mono);

    AudioStream *stream = nullptr;
    builder.openStream(&stream);

    int sampleRate = stream->getSampleRate();
    int numVoices = 32;
    int numFrames = stream->getFramesPerBurst();
    PresetWaveform waveform = Triangle;

    synth = new Synth(sampleRate, numVoices, numFrames, waveform);
    synth->setVolume(0.5);
    stream ->requestStart();
}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    auto *outputData = static_cast<float *>(audioData);

    // Ensure outputData is filled with 0's
    for (int i = 0; i < numFrames; ++i){
        outputData[i] = 0;
    }

    synth->renderAudio(outputData, numFrames);

    //Limit audio (will cause clipping)
    for (int i = 0; i < numFrames; ++i){
        if (outputData[i] > 1) {
            outputData[i] = 1;
        } else if (outputData[i] < -1) {
            outputData[i] = -1;
        }
    }

    return oboe::DataCallbackResult::Continue;
}

