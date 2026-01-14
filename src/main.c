#include "window.h"
#include "keyboard.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{

	as_Window window;
	bool* keyboard = as_keyalloc();
	if (as_windowinit(&window))
	{
		printf("Error: could not initialize window.\n");
		return 1;
	}
	
	while (window.isopen)
	{
		as_windowupdate(&window, keyboard);
	}
	free(keyboard);
	as_windowclose(&window);
  return 0;
}
