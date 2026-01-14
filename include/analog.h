#pragma once

#define MIN_VOLTAGE 0.001
#define OPAMP_GAIN 1

typedef struct as_DspCapacitor
{
	float C;
	float voltage;
	float coef;
} as_DspCapacitor;

typedef struct as_DspOpamp
{
	float Vout;
} as_DspOpamp;

float as_opamp_process(as_DspOpamp* opamp, float Vplus, float Vminus);

void as_capacitor_setR(as_DspCapacitor* cap, float R);

float as_capacitor_process(as_DspCapacitor* cap, float Vin);

float as_diode_getR(float V);

float as_parallelR(float R1, float R2);

float as_vdiv(float V, float R1, float R2);


