#pragma once

#define SUPPLY_VOLTAGE 12
#define MIN_VOLTAGE 0.001
#define LEAKAGE_R 1.0e12
#define OPAMP_GAIN 1
#define OPAMP_CLIPPING 0.9
#define KEYBOARD_STEP_R 1000.0f
#define KEYBOARD_TUNE_R 61000.0f

/**
* @struct as_DspCapacitor
* @brief Stores parameters of a capacitor.
*/
typedef struct as_DspCapacitor
{
	float C; /** The capacitance, in Farads **/
	float voltage; /** The current voltage stored in the capacitor **/
	float coef; /** The filtering coeficient calculated from Thevenin resistance **/
} as_DspCapacitor;

/**
* @struct as_DspOpamp
* @brief stores the voltage accumulated on the opamp's output
*/
typedef struct as_DspOpamp
{
	float Vout;
} as_DspOpamp;

/**
* @brief Processes an opamp's inputs and sets its output
*
* @param opamp  pointer to the opamp
* @param Vplus  the voltage at the non-inverting input
* @param Vminus the voltage at the inverting input
*
* @return the opamp's output voltage
*/
float as_opamp_process(as_DspOpamp* opamp, float Vplus, float Vminus);

/**
* @brief Sets capacitor's parameters from the Thevenin resistance across the capacitor.
*
* @param cap  pointer to the capacitor
* @param R  the Thevenin resistance across the capacitor, in ohms
*/
void as_capacitor_setR(as_DspCapacitor* cap, float R);

/**
* @brief Processes the Thevenin voltage at a capacitor's terminals
* 
* @param cap  pointer to the capacitor
* @param Vin  the Thevenin voltage across the capacitor's terminals
*
* @return the output voltage across the capacitor
*/
float as_capacitor_process(as_DspCapacitor* cap, float Vin);

/**
* @brief Calculates the effective resistance of a diode based on the voltage across it
* 
* @param V  the voltage across the diode
*
* @return the diode's effective resistance, based on its current characteristic curve
*/
float as_diode_getR(float V);

/**
* @brief Calculate the resistance of two resistors in parallel
* 
* @param R1  The first resistance in ohms
* @param R2  The second resistance in ohms
*
* @return the parallel resistance
*/
float as_parallelR(float R1, float R2);

/**
* @brief Calculate the output voltage of a voltage divider
* 
* @param V  The supply voltate across both resistors
* @param R1  The first resistance in ohms
* @param R2  The first resistance in ohms
*
* @return The voltage between both resistors
*/
float as_vdiv(float V, float R1, float R2);

/**
* @brief Calculate the Thevenin voltage and resistance of the keyboard divider circuit.
*
* @param Vout  pointer to the output voltage
* @param Rout  pointer to the output resistance
* @param note  the number of the pressed key (-1 is none pressed)
*/
void as_keyboardcap_vr(float* Vout, float* Rout, int note);
