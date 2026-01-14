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

bool as_windowinit(as_Window* window)
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

	window->isopen = true;
	
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
		}
	}
	SDL_UpdateWindowSurface(window->sdlwindow);
	SDL_Delay(1000 / WINDOW_FRAMERATE);
}

void as_windowclose(as_Window* window)
{
	SDL_Quit();
}

