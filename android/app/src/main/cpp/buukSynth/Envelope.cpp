#include "Envelope.h"

Envelope::Envelope(int sampleRate, float aTime, float dTime, float sustainAmp, float rTime)
{
	mSampleRate = sampleRate;
	setAttack(aTime);
	setDecay(dTime);
	setSustain(sustainAmp);
	setRelease(rTime);
}

Envelope::~Envelope()
{
}

void Envelope::setAttack(float time)
{
	attrNumSamples = (int)(time * mSampleRate);
}

void Envelope::setDecay(float time)
{
	decNumSamples = (int)(time * mSampleRate);
}

void Envelope::setSustain(float amplitude)
{
	susAmp = amplitude;
}

void Envelope::setRelease(float time)
{
	relNumSamples = (int)(time * mSampleRate);
}

void Envelope::setWaveOn(bool isWaveOn)
{
	mIsWaveOn = isWaveOn;
}

void Envelope::renderAudio(float* audioData, int numFrames)
{
	for (int i = 0; i < numFrames; ++i) {
		if (mIsWaveOn) {
			//Reset Release
			//Move these to setWaveOn function
			relCount = 0;

			//ASDR Amp Shaping
			if (timeSamples <= attrNumSamples) {
				waveAmp = lerp(0, 1, ((float)attrCount / (float)attrNumSamples));
				audioData[i] = waveAmp * audioData[i];
				++attrCount;
				++timeSamples;
			}
			else if (timeSamples <= (attrNumSamples + decNumSamples)) {
				waveAmp = lerp(1, susAmp, ((float)decCount / (float)decNumSamples));
				audioData[i] = waveAmp * audioData[i];
				++decCount;
				++timeSamples;
			}
			else {
				waveAmp = susAmp;
				audioData[i] = waveAmp * audioData[i];
			}
		}
		else {
			//Reset ADSR sample timestamps
			//Move these to setWaveOn function
			timeSamples = 0;
			attrCount = 0;
			decCount = 0;

			if (relCount <= relNumSamples) {
				audioData[i] = lerp(waveAmp, 0, ((float)relCount / (float)relNumSamples)) * audioData[i];
				++relCount;
			}
			else {
				audioData[i] = 0;
			}

		}
	}

}

float Envelope::lerp(float a, float b, float t)
{
	return  ((1 - t) * a) + (t * b);;
}
