#include "window.h"
#include "keyboard.h"

#include <stdio.h>
#include <stdlib.h>

#include "analog.h"
#include "dsp.h"

int main(int argc, char** argv)
{

	as_Window window;
	as_DspData dspdata;
	bool* keyboard = as_keyalloc();
	
	if (as_windowinit(&window, &dspdata))
	{
		printf("Error: could not initialize window.\n");
		as_windowclose(&window);
		return 1;
	}

	as_dspinit(&dspdata);


	as_guiaddknob(&window.gui, 100, 100, &dspdata.vco_scale);
	as_guiaddtext(&window.gui, 50, 200, "VCO SCALE");
	as_guiaddknob(&window.gui, 200, 100, &dspdata.vco_tune);
	

	while (window.isopen)
	{
		as_windowupdate(&window, keyboard);
	}
	free(keyboard);
	as_windowclose(&window);
  return 0;
}
