#include "Waveform.h"

Waveform::Waveform()
{
	setWaveform(Sine);
}

Waveform::Waveform(PresetWaveform waveform)
{
	setWaveform(waveform);
}

Waveform::~Waveform() 
{
}

float Waveform::lookup(float phase) {
	//Ensure phase < two pi
	if (phase > TWO_PI) {
		phase = fmod(phase, TWO_PI);
	}

	float sampleIdxExact = ((float)waveform.size() * (phase / TWO_PI));
	int leftSampleIdx = (int)sampleIdxExact % waveform.size();
	int rightSampleIdx = (leftSampleIdx + 1) % waveform.size();
	float leftSample = waveform.at(leftSampleIdx);
	float rightSample = waveform.at(rightSampleIdx);
	float t = sampleIdxExact - (float)leftSampleIdx;

	//Lerp
	float sample = ((1 - t) * leftSample) + (t * rightSample);
	return sample;
}

void Waveform::setWaveform(PresetWaveform table) {
	switch (table) {
	case Sine:
		fillWaveform(&sineWaveform);
		break;
	case Square:
		fillWaveform(&squareWaveform);
		break;
	case Saw:
		fillWaveform(&sawWaveform);
		break;
	case Triangle:
		fillWaveform(&triangleWaveform);
		break;
	}
}

void Waveform::fillWaveform(const std::vector<float>* buffer) {
	//Empty waveform
	waveform.clear();

	//Copy preset waveform to out waveform
	for(int i = 0; i < buffer->size(); ++i) {
		waveform.push_back(buffer->at(i));
	}
}