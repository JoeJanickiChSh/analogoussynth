#pragma once

#define SAMPLERATE 44100

typedef struct as_DspData
{
	float util_at0;
	float util_at1;

	float lfo_speed;
	
	float eg_attack;
	float eg_release;
	
	float vco_scale;
	float vco_tune;
	float vco_pw;
	
	float vcf_cutoff;
	float vcf_resonance;
	float vcf_cv;

	float vca_gain;

	float out_drive;
	float out_gain;
} as_DspData;

void as_dspinit(as_DspData* dspdata);
