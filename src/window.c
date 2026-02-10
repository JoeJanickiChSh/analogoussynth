#include "window.h"
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>

const int keylookup[KB_NUM_KEYS] = 
{
	SDLK_z, SDLK_s, SDLK_x, SDLK_d, SDLK_c, SDLK_v, SDLK_g, SDLK_b, SDLK_h, SDLK_n, SDLK_j, SDLK_m, 
  SDLK_q, SDLK_2, SDLK_w, SDLK_3, SDLK_e, SDLK_r, SDLK_5, SDLK_t, SDLK_6, SDLK_y, SDLK_7, SDLK_u 
};

int key2note(int sdlkey)
{
	for (int i = 0; i < KB_NUM_KEYS; i++)
	{
		if (keylookup[i] == sdlkey)
			return i;
	}
	return -1;
}

void print_sdl_error()
{
	printf("SDL_Error: %s\n", SDL_GetError());
}

bool as_windowinit(as_Window* window, as_DspData* dspdata)
{
	window->isopen = false;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		print_sdl_error();
		return true;
	}
	window->sdlwindow = SDL_CreateWindow(WINDOW_TITLE,
												SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
												WINDOW_WIDTH_DEFAULT, WINDOW_HEIGHT_DEFAULT,
												SDL_WINDOW_SHOWN);
	if (window->sdlwindow == NULL)
	{
		print_sdl_error();
		return true;
	}

	window->surface = SDL_GetWindowSurface(window->sdlwindow);
	window->dspdata = dspdata;

	window->isopen = true;

	window->colorkey = SDL_MapRGB(window->surface->format, 255, 0, 255);
	
	if (as_guiinit(&window->gui, window->colorkey))
	{
		printf("Error opening animation files.\n");
		return true;
	}
	
	
	for (int i = 0; i < KB_NUM_KEYS; i++)
		window->keystates[i] = 0.0f;
	
	
	return false;
}

void as_windowupdate(as_Window* window, bool* keyboard)
{
	SDL_Event event;
	int note_index;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			window->isopen = false;
			return;

		case SDL_KEYDOWN:
			note_index = key2note(event.key.keysym.sym);
			if (note_index != -1)
				keyboard[note_index] = true;
			break;

		case SDL_KEYUP:
			note_index = key2note(event.key.keysym.sym);
			if (note_index != -1)
				keyboard[note_index] = false;
			break;

		case SDL_MOUSEMOTION: window->mousex = event.motion.x;
			window->mousey = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			window->mousedown = true;
			break;

		case SDL_MOUSEBUTTONUP:
			window->mousedown = false;
			break;
		}
	}
	for (int i = 0; i < KB_NUM_KEYS; i++)
		window->keystates[i] += 0.5 * ((keyboard[i] ? 7.0f : 0.0f) - window->keystates[i]);

	window->keynum = -1;
	for ( int i = KB_NUM_KEYS - 1; i >= 0; i--)
	{
		if (keyboard[i])
		{
			window->keynum = i;
			break;
		}
	}

	as_guidraw(&window->gui, window->surface, window->mousedown, window->mousex, window->mousey);

	int keyheight = WINDOW_HEIGHT_DEFAULT - window->gui.anim.key->height - 1;
	int keywidth = window->gui.anim.key->width;
	
	int xind = 0;
	for (int i = 0; i < KB_NUM_KEYS; i++) {
		int octavekey = i % 12;
		int drawkey = 0;
		if (octavekey == 1 || octavekey == 3 || octavekey == 6 || octavekey == 8 || octavekey == 10) {
			drawkey = 2;
			xind--;
		}
		if (octavekey == 4 || octavekey == 11)
			drawkey = 1;
		as_animationdraw(window->gui.anim.key,150+xind*keywidth, keyheight , window->keystates[i], drawkey, window->surface);
		xind ++;
	}

	SDL_UpdateWindowSurface(window->sdlwindow);
	SDL_Delay(1000 / WINDOW_FRAMERATE);
	window->frametimer++;
}

void as_windowclose(as_Window* window)
{
	as_guifree(&window->gui);
	SDL_Quit();
}

