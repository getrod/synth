#ifndef ENVELOPE_H
#define ENVELOPE_H

const float MIN_TIME = 0.0005;

class Envelope
{
public:
	Envelope(int sampleRate, float aTime, float dTime, float sustainAmp, float rTime);
	~Envelope();

	void setAttack(float time);
	void setDecay(float time);
	void setSustain(float amplitude);
	void setRelease(float time);
	void setWaveOn(bool isWaveOn);
	void renderAudio(float* audioData, int numFrames);

private:
	int timeSamples = 0;
	int attrCount = 0;
	int attrNumSamples = 0;
	int decCount = 0;
	int decNumSamples = 0;
	int relCount = 0;
	int relNumSamples = 0;
	int mSampleRate = 44100;
	float susAmp = 0;
	float waveAmp = 0;
	bool mIsWaveOn = false;

	float lerp(float a, float b, float t);
};

#endif

