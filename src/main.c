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

	/** Util Module **/
	as_guiaddtext(&window.gui, 56, 0, "ATTEN");
	as_guiaddtext(&window.gui, 72, 8+2*64, "SUM");

	as_guiaddjack(&window.gui, 0, 8, 0);
	as_guiaddjack(&window.gui, 0, 8+64, 0);

	as_guiaddjack(&window.gui, 0, 16+2*64, 0);
	as_guiaddjack(&window.gui, 0, 16+3*64, 0);

	as_guiaddknob(&window.gui, 64, 8, &dspdata.util_at0);
	as_guiaddknob(&window.gui, 64, 8+64, &dspdata.util_at1);

	as_guiaddjack(&window.gui, 64, 16+2*64, 0);
	as_guiaddjack(&window.gui, 64, 16+3*64, 0);

	as_guiaddjack(&window.gui, 128, 8, 0);
	as_guiaddjack(&window.gui, 128, 8+64, 0);
	as_guiaddjack(&window.gui, 128, 16+2*64, 0);
	as_guiaddjack(&window.gui, 128, 16+3*64, 0);

	/** LFO Module **/
	as_guiaddtext(&window.gui, 264, 0, "LFO");

	as_guiaddknob(&window.gui, 256, 16, &dspdata.lfo_speed);
	as_guiaddtext(&window.gui, 248, 16+64, "SPEED");

	as_guiaddjack(&window.gui, 256, 16+64, 0);
	as_guiaddtext(&window.gui, 264, 16+64+64, "OUT");

	/** Envelope Module **/

	as_guiaddtext(&window.gui, 392, 0, "ENV");

	as_guiaddknob(&window.gui, 384, 16, &dspdata.eg_attack);
	as_guiaddtext(&window.gui, 392, 16+64, "ATK");
	as_guiaddknob(&window.gui, 384, 16+64, &dspdata.eg_release);
	as_guiaddtext(&window.gui, 392, 16+128, "REL");
	as_guiaddjack(&window.gui, 384, 16+128, 0);
	as_guiaddtext(&window.gui, 384, 16+128+64, "GATE");
	as_guiaddjack(&window.gui, 384, 16+128+64, 0);
	as_guiaddtext(&window.gui, 392, 16+128+128, "OUT");

	while (window.isopen)
	{
		as_windowupdate(&window, keyboard);
	}
	free(keyboard);
	as_windowclose(&window);
  return 0;
}
