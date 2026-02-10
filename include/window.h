#pragma once
#include "dsp.h"
#include "animation.h"
#include "keyboard.h"
#include "gui.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_FRAMERATE 30
#define WINDOW_TITLE "Analogous"
#define WINDOW_WIDTH_DEFAULT 800
#define WINDOW_HEIGHT_DEFAULT 600

/**
* @struct as_Window
* @brief Stores data for managing the application's window.
*/
typedef struct as_Window
{
	bool isopen; /** Stores whether or not the window is currently open.*/
	SDL_Window* sdlwindow; /** The SDL window object */
	SDL_Surface* surface; /** The window's rendering surface */
	int colorkey; /** The transparency key in the screen's pixel format **/
	as_Gui gui;
	float keystates[KB_NUM_KEYS]; /** The animation state of each keyboard key **/
	unsigned int frametimer; /** Counts the current frame **/
	int keynum; /** The number of the highest pressed key (-1 if none) **/
	bool mousedown;
	int mousex;
	int mousey;
	as_DspData* dspdata;
} as_Window;

/**
* @brief Initializes the window.
*
* @param window  pointer to the window structure.
* @param dspdata  pointer to the DSP data structure.
*
* @return false on success
* @return true on failure
*/
bool as_windowinit(as_Window* window, as_DspData* dspdata);

/**
* @brief Updates the window, including rendering and events.
*
* @param window  pointer to the window structure.
* @param keyboard  pointer to the keyboard state.
*/
void as_windowupdate(as_Window* window, bool* keyboard);

/**
* @brief closes the window, freeing all allocated memory.
*
* @param window  pointer to the window structure.
*/
void as_windowclose(as_Window* window);
