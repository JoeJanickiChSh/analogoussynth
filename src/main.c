#include "window.h"
#include "keyboard.h"

#include <stdio.h>
#include <stdlib.h>

#include "analog.h"

int main(int argc, char** argv)
{

	as_Window window;
	bool* keyboard = as_keyalloc();
	if (as_windowinit(&window))
	{
		printf("Error: could not initialize window.\n");
		as_windowclose(&window);
		return 1;
	}
	as_DspCapacitor kbcap = {22.0e-12, 0, 0};
	float capV = 0;
	float capR = 0;
	
	while (window.isopen)
	{
		as_keyboardcap_vr(&capV, &capR, window.keynum);
		as_capacitor_setR(&kbcap, capR);
		printf("Voltage: %f\n", as_capacitor_process(&kbcap, capV));
		as_windowupdate(&window, keyboard);
	}
	free(keyboard);
	as_windowclose(&window);
  return 0;
}
