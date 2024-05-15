#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "Waveform.h"

const float DEFAULT_FREQUENCY = 440.0;
const int DEFAULT_SAMPLERATE = 44100;

class Oscillator
{
public:
	Oscillator();
	~Oscillator();

	void setSampleRate(int sampleRate);
	void setFrequency(double frequency);
	void setAmplitude(float amplitude);
	void setWavetable(PresetWaveform table);
	void renderAudio(float* audioData, int numFrames);

private:
	Waveform mWaveform;
	float mPhase = 0;
	float mAmplitude = 0;
	float mPhaseIncrement = 0;
	float mFrequency = DEFAULT_FREQUENCY;
	int mSampleRate = DEFAULT_SAMPLERATE;

	void updatePhaseIncrement();
};
#endif

