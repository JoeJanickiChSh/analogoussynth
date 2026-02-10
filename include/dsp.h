#pragma once

#define SAMPLERATE 44100

typedef struct as_DspData
{
	float vco_scale;
	float vco_tune;
} as_DspData;

void as_dspinit(as_DspData* dspdata);
