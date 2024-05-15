#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include <math.h>
#include "WaveformUtils.h"

class Waveform
{
public:
	Waveform();
	Waveform(PresetWaveform waveform);
	~Waveform();
	float lookup(float phase);
	void setWaveform(PresetWaveform waveform);
private:
	std::vector<float> waveform;
	void fillWaveform(const std::vector<float>* buffer);
};

#endif

