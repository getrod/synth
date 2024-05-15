#include "Oscillator.h"

Oscillator::Oscillator()
{
}

Oscillator::~Oscillator()
{
}

void Oscillator::renderAudio(float* audioData, int numFrames) {
	for (int i = 0; i < numFrames; ++i) {
		audioData[i] = mAmplitude * mWaveform.lookup(mPhase);

		mPhase += mPhaseIncrement;
		if (mPhase > TWO_PI) {
			mPhase -= TWO_PI;
		}
	}
}

void Oscillator::updatePhaseIncrement() {
	mPhaseIncrement = TWO_PI * mFrequency * (1 / (float)mSampleRate);
}

void Oscillator::setSampleRate(int sampleRate) {
	mSampleRate = sampleRate;
	updatePhaseIncrement();
}

void Oscillator::setFrequency(double frequency) {
	mFrequency = (float)frequency;
	updatePhaseIncrement();
}

void Oscillator::setAmplitude(float amplitude) {
	mAmplitude = amplitude;
}

void Oscillator::setWavetable(PresetWaveform waveform) {
	mWaveform.setWaveform(waveform);
}





