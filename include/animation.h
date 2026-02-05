#pragma once
#include <SDL2/SDL.h>

typedef struct as_Animation
{
	int width;
	int height;
	SDL_Surface* surface;
	
} as_Animation;

as_Animation* as_animationnew(const char* filename, int width, int height, int colorkey);

void as_animationdraw(as_Animation* anim, int x, int y, int framex, int framey, SDL_Surface* target);

void as_animationfree(as_Animation* anim);
