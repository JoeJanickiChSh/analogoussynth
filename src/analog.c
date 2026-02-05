#include "analog.h"
#include "dsp.h"
#include "keyboard.h"
#include <stdio.h>

/**
* The voltage across a capacitor is described the formula:
* V = V + (1 - exp( -1 / (SAMPLERATE * r * c)  )) * (Vtarget - V)
*
* This can be separated to V = V + coef * (Vtarget - V)
* where coef = 1 - exp( -1 / (SAMPLERATE * r * c) ).
* Since 1 / (SAMPLERATE * r * c) yields small values for most r and c values (< 1),
* the taylor expansion of e^x can be used:
*   x = 1 / SAMPLERATE * r * c
*   coef = x - 0.5 * x * x   // coef = 1 - 1 - (-x) - 0.5 * (-x)^2
*/

void as_capacitor_setR(as_DspCapacitor* cap, float R)
{
	float x = 1.0 / (SAMPLERATE * R * cap->C);
	if (x > 1)
		x = 1;
	if (x < 0)
		x = 0;
	cap->coef = x - 0.5 * x * x;
	
}

float as_capacitor_process(as_DspCapacitor* cap, float Vin)
{
	cap->voltage += cap->coef * (Vin - cap->voltage);
	return cap->voltage;
}

/**
* Using diode characteristic approximation where:
* I = 1.6 * V * V
*/
float as_diode_getR(float V)
{
	if (V < MIN_VOLTAGE)
		V = MIN_VOLTAGE;
	return (1.0 / 1.6 * V);
}

float as_parallelR(float R1, float R2)
{
	if (R1 + R2 == 0.0)
		return 0.0;
	return (R1 * R2) / (R1 + R2);
}

float as_vdiv(float V, float R1, float R2)
{
	if (R1 + R2 == 0.0)
		return 0;
	return (V * R1) / (R1 + R2);
}

float as_opamp_process(as_DspOpamp* opamp, float Vplus, float Vminus)
{
	opamp->Vout += OPAMP_GAIN * (Vplus - Vminus);
	if (opamp->Vout < -SUPPLY_VOLTAGE * OPAMP_CLIPPING)
		opamp->Vout = -SUPPLY_VOLTAGE * OPAMP_CLIPPING;
	else if (opamp->Vout > SUPPLY_VOLTAGE * OPAMP_CLIPPING)
		opamp->Vout = SUPPLY_VOLTAGE * OPAMP_CLIPPING;
}





/**
* Resistor ladder connected by switches
* 
*  Vcc -------+
*             |
*            [ ] Ra
*             |       /
*             +------o o--+         +------+
*             |           |         | |\   |
*            [ ] Rb       |         +-|-\  |
*             |       /   |           |  >-+---
*             +------o o--+---+-------|+/
*             |               |       |/
*            [ ] Ra           = C
*             |               |
*             V               V
*/
void as_keyboardcap_vr(float* Vout, float* Rout, int note)
{
	if (note < 0) {
		*Vout = 0.0f;
		*Rout= LEAKAGE_R;
		return;
	}
	float Rl = KEYBOARD_TUNE_R + note * KEYBOARD_STEP_R;
	float Ru = KEYBOARD_TUNE_R + (KB_NUM_KEYS - note - 1) * KEYBOARD_STEP_R;
	*Vout = as_vdiv(SUPPLY_VOLTAGE, Rl, Ru);
	*Rout = as_parallelR(Rl, Ru);
}
