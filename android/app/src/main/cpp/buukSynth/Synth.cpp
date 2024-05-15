#include "Synth.h"

Synth::Synth(int sampleRate, int numVoices, int numFrames, PresetWaveform waveform)
{
	mNumVoices = numVoices;
	mOscillators = new Oscillator* [numVoices];
	mEnvelopes = new Envelope*[numVoices];

	mVoiceBuffer = new float[numFrames];

	for (int i = 0; i < numVoices; ++i) {
		mOscillators[i] = new Oscillator();
		mOscillators[i]->setAmplitude(1);
		mOscillators[i]->setSampleRate(sampleRate);
		mOscillators[i]->setWavetable(waveform);

		mEnvelopes[i] = new Envelope(
			sampleRate,
			0.005,		//A
			0.10,		//D
			0.5,		//S
			0.25		//R
		);
	}
}

Synth::~Synth()
{
	//Delete all ocsillators & envelopes
	//Delete voice buffer
}

void Synth::noteOff(int noteId)
{
	int voiceId = noteId % mNumVoices;
	mEnvelopes[voiceId]->setWaveOn(false);
}

void Synth::noteOn(int noteId, float freq)
{
	int voiceId = noteId % mNumVoices;
	mOscillators[voiceId]->setFrequency(freq);
	mEnvelopes[voiceId]->setWaveOn(true);
}

void Synth::setVolume(float volume)
{
	mVolume = volume;
}

void Synth::renderAudio(float* audioData, int numFrames)
{
	//Ensure audioData has 0's
	for (int i = 0; i < mNumVoices; ++i) {
		mOscillators[i]->renderAudio(mVoiceBuffer, numFrames);
		mEnvelopes[i]->renderAudio(mVoiceBuffer, numFrames);

		for (int j = 0; j < numFrames; ++j) {
			audioData[j] += mVolume*mVoiceBuffer[j];
		}
	}
}
