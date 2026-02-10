#include "dsp.h"

void as_dspinit(as_DspData* dspdata)
{
	dspdata->vco_scale = 0.5;
	dspdata->vco_tune = 0.5;
	dspdata->vco_pw = 0.5;

	dspdata->util_at0 = 1.0;
	dspdata->util_at1 = 1.0;
	
	dspdata->lfo_speed = 0.5;

	dspdata->eg_attack = 0.0;
	dspdata->eg_release = 0.0;

	dspdata->vcf_cutoff = 1.0;
	dspdata->vcf_resonance = 0.0;
	dspdata->vcf_cv = 0.0;

	dspdata->vca_gain = 1.0;

	dspdata->out_drive = 0.5;
	dspdata->out_gain = 0.5;
}

