#ifndef SYNTH_H
#define SYNTH_H

#include "Oscillator.h"
#include "Envelope.h"
class Synth
{
public:
	Synth(int sampleRate, int numVoices, int numFrames, PresetWaveform waveform);
	~Synth();
	void noteOff(int noteId);
	void noteOn(int noteId, float freq);
	void setVolume(float volume);
	void renderAudio(float* audioData, int numFrames);
private:
	Oscillator** mOscillators;
	Envelope** mEnvelopes;
	int mNumVoices = 4;
	float mVolume = 0.8;
	float* mVoiceBuffer;
};

#endif
