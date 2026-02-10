#include "animation.h"
#include <stdlib.h>

as_Animation* as_animationnew(const char* filename, int width, int height, int colorkey)
{
	as_Animation* anim = malloc(sizeof(as_Animation));
	anim->width = width;
	anim->height = height;
	anim->surface = SDL_LoadBMP(filename);
	if (!anim->surface)
		return NULL;

	SDL_SetColorKey(anim->surface, SDL_TRUE, colorkey);
	return anim;
}

void as_animationdraw(as_Animation* anim, int x, int y, int framex, int framey, SDL_Surface* target)
{
	SDL_Rect sprite_pos = {x, y, 0, 0};
	SDL_Rect sprite_crop = {framex * anim->width, framey * anim->height, anim->width, anim->height};
	SDL_BlitSurface(anim->surface, &sprite_crop, target, &sprite_pos);
}

void as_animationfree(as_Animation* anim)
{
	free(anim);
}

